#include "../../include/server/game_controller.hpp"
#include <iostream>

//constructor, constructs game_state
Game_Controller::Game_Controller()
{
    game_state = new Game_State();
}

void Game_Controller::eval_request(const Player_id& player_id, const std::string& msg)
{
    // std::cout<<"evaluating request"<<std::endl;	
    nlohmann::json request = nlohmann::json::parse(msg);
    //const size_t type = request["type"];
    //Request_Type request_type = Request_Type(type);
    Request_Type request_type =  request["type"];

    switch (request_type)
    {
        case Request_Type::NEW_PLAYER:
	    {
	        //eval_new_player_request(request);
		    Player_id player_id = request["id"]; //retrieve player id
	    std::string player_name = request["name"];
	    if(!game_state->check_if_player_exists(player_id))
                add_new_player(player_id, player_name);
            break;
	    }
        case Request_Type::START_GAME:
        {
            Player_id player_id = request["id"];
            //check if game has already started
            if (game_state->get_has_started())
            {
                nlohmann::json error_respond;
                error_respond["type"] = Respond_Type::ERROR_;
                error_respond["msg"] = "ERROR: game is already ongoing";
                net::TCP_Server::sendToPlayer(player_id, error_respond.dump());
            }
            else if(game_state->get_players().size() <= 1)
            {
                nlohmann::json error_respond;
                error_respond["type"] = Respond_Type::ERROR_;
                error_respond["msg"] = "ERROR: only one player playing";
                net::TCP_Server::sendToPlayer(player_id, error_respond.dump());
            }
	        else
            {
                //set has_started to 1
                game_state->set_has_started(true);
                //retrieve first player
                Player *first_player = game_state->get_player(player_id);
                first_player->set_players_turn(true);
                game_state->set_current_player(first_player->get_player_id());
                //should we set and send the discard_pile just now, what to use as default when constructing,
                //send Hand to players
                std::vector<std::pair<Player_id, Player*> > players = game_state->get_players();
                for(auto& elem : players)
                {
                    send_hand(elem.first);
                }

                broadcast_game_state();
            }
            break;
	    }
        case Request_Type::PLAY_REQUEST:
	    {
	        Player_id player_id = request["id"];
	        //check if player is allowed to play
            if(player_id == game_state->get_current_player())
            {
                ck_Cards::Cards card = request["card"];
                //check if this is a valid move (e.g is compatible with top_card)
                bool valid_card = valid_move(card);

                if(valid_card)
                {
                    //add the card to discard_pile
                    game_state->get_discard_pile().push(card);
                    //delete from player hand
                    Player* player = game_state->get_player(player_id);
                    player->get_hand().remove(card);
                    send_hand(player_id);
                    //UNO
                    if(player->number_of_cards()==1)
                    {
                        nlohmann::json popup;
                        popup["type"] = Respond_Type::UNO;
			            popup["id"]= player_id;
                        net::TCP_Server::broadcast(popup.dump());
                        //evaluate effect of card
                        effect_of_card(player_id, card);
                    }
                    //check if player has won
                    else if(player->get_hand().empty())
                    {
                       player->set_has_won(true);
                       const std::string player_name = player->get_player_name();

                        nlohmann::json popup;
                        popup["type"] = Respond_Type::WINS;
                        popup["player_name"] = player->get_player_name();
                        popup["id"] = player->get_player_id();
                        net::TCP_Server::broadcast(popup.dump());
                       //finish game
                       if(game_state->have_all_won())
                       {

                           nlohmann::json popup;
                           popup["type"] = Respond_Type::START_NEW_GAME; //maybe start new game
                           net::TCP_Server::broadcast(popup.dump());
                           broadcast_game_state();
                           
                           // Sleeps 1 sec to finish up send and receieve queues.
                           sleep(1);
                           delete game_state;
                           net::TCP_Server::terminate();

                           // Resetting the game doesn't quite work
                           //reset_game();
                       }
                       else
                       {
                           //evaluate effect of card
                           effect_of_card(player_id, card);
                       }
                    }
                    else {
                        //evaluate effect of card
                        effect_of_card(player_id, card);
                    }

                }
                else //error message
                {

                    const ck_Cards::Card& card_object = ck_Cards::Deck::get(game_state->get_discard_pile().get_top_card());
                    nlohmann::json error_respond;
                    error_respond["type"] = Respond_Type::ERROR_;
                    std::stringstream error_msg;
                    if(card_object.action == ck_Cards::Action::NONE)
                    {
                        error_msg << "ERROR: please play a " << ck_Cards::get_color_as_string(game_state->get_color_to_be_matched()) << " card or a card with the same number.";
                    }
                    if(card_object.value == ck_Cards::Value::NONE)
                    {
                        error_msg << "ERROR: please play a " << ck_Cards::get_color_as_string(game_state->get_color_to_be_matched()) << " card or a " << card_object.get_action_as_string() << " card";
                    }
                    error_respond["msg"] = error_msg.str();
                    net::TCP_Server::sendToPlayer(player_id, error_respond.dump());
                }
            }
            break;
	    }
        case Request_Type::DRAW_REQUEST:
	    {
            Player_id player_id = request["id"];
            Player* player = game_state->get_player(player_id);
            //check if allowed to draw
	        if(game_state->get_current_player() == player_id && !(player->get_has_won()))
            {
                //retrieve a card from draw_pile and add to hand
                draw_card(player_id);

                //send hand
                send_hand(player_id);

                //switch players turn
                switch_player(player_id);

                //broadcast game_update
                broadcast_game_state();
            }
            break;
	    }
        case Request_Type::EXIT_REQUEST:
	    {
            Player_id player_id = request["id"];
            //check how many players are in the game
            unsigned int number_of_players = game_state->get_players().size();
            // net::TCP_Server::disconect(player_id);
            if(number_of_players == 1)
            {
                //terminate and clean up
                sleep(1);
                delete game_state;
                net::TCP_Server::terminate();
            }
            if(number_of_players == 2)
            {
                Player* player = game_state->get_player(player_id);
                //skip player if he is currently playing
                if(game_state->get_current_player() == player_id)
                {
                    switch_player(player_id);
                }
                //add hand to draw_pile
                const std::list<ck_Cards::Cards> hand = player->get_hand().get_cards();
                game_state->get_draw_pile().push(hand);

                //remove player from players vector and delete it
                game_state->remove_player(player_id);
                //cap connection
                net::TCP_Server::disconect(player_id);
                //set has won
                Player_id next_player_id = game_state->get_current_player(); //single player in game
                Player* next_player = game_state->get_player(next_player_id);
                next_player->set_has_won(true);


                broadcast_game_state();

                nlohmann::json popup;
                popup["type"] = Respond_Type::WINS;
                popup["player_name"] = next_player->get_player_name();
                popup["id"] = next_player->get_player_id();
                net::TCP_Server::broadcast(popup.dump());

                broadcast_game_state();

                nlohmann::json popup2;
                popup2["type"] = Respond_Type::START_NEW_GAME; //maybe start new game
                net::TCP_Server::broadcast(popup2.dump());
                broadcast_game_state();


                //terminate and clean up
                sleep(1);
                delete game_state;
                net::TCP_Server::terminate();

            }
            else
            {
                Player* player = game_state->get_player(player_id);

                //skip player if he is currently playing
                if(game_state->get_current_player() == player_id)
                {
                    switch_player(player_id);
                }

                //add hand to draw_pile
                const std::list<ck_Cards::Cards> hand = player->get_hand().get_cards();
                game_state->get_draw_pile().push(hand);

                //remove player from players vector and delete player
                game_state->remove_player(player_id);
                net::TCP_Server::disconect(player_id);

                broadcast_game_state();
                //disconnect connection
                //net::TCP_Server::disconnect(player_id);
            }
            break;
	    }
        case Request_Type::SELECTED_COLOR:
        {
            Player_id player_id = request["id"];

            //check if player is allowed to select color
            if(game_state->get_current_player() == player_id)
            {
                ck_Cards::Color color = request["color"];
                game_state->set_color_to_be_matched(color);
                //switch player
                switch_player(player_id);
                broadcast_game_state();

            }
        }
    }
}


/////////////////////add_new_player//////////////////////////////////////////////////

void Game_Controller::add_new_player(const Player_id& _player_id, const std::string& player_name)
{
        //create hand
        std::list<ck_Cards::Cards> hand_list;//(7);->otherwise list will end up beeing of size 14
        for (unsigned int i = 0; i < 7; ++i)
        {
            ck_Cards::Cards card = game_state->get_draw_pile().get_top_card(); //get cards from draw_pile
            hand_list.push_back(card);
        } 

        //construct a new player
        Player* player = new Player(_player_id, player_name);
        player->get_hand().push(hand_list);

        //add_player to player list of game_state
        game_state->add_Players(player);

        //broadcast game_update
        broadcast_game_state();
}

//////////////////////////////////////broadcast game state////////////////////////////////////

void Game_Controller::broadcast_game_state() const
{
    //broadcast game_update
    nlohmann::json respond;
    respond["type"] = Respond_Type::GAME_UPDATE;
    //add player_name and number of cards of all players
    respond["players"] = nlohmann::json::array();
    for(auto iterator : game_state->get_players())
    {
        Player* player = iterator.second;
        nlohmann::json player_info = nlohmann::json::array({{"Player_id", player->get_player_id()}, {"Player_name", player->get_player_name()}, {"number_of_cards", player->number_of_cards()}});
        respond["players"].push_back(player_info);
    }
    respond["current_player"] = game_state->get_current_player();
    respond["color_to_be_matched"] = game_state->get_color_to_be_matched();
    respond["top_card"] = game_state->get_discard_pile().back();
    net::TCP_Server::broadcast(respond.dump());
}
///////////////////////////////////send_hand/////////////////////////////////////////////////

void Game_Controller::send_hand(const Player_id& player_id)
{
    Player* player = game_state->get_player(player_id);
    nlohmann::json respond;
    respond["type"] = Respond_Type::SEND_HAND;
    //TODO: maybe not the best way to send cards rather send whole hand
    respond["hand"] = player->get_hand().get_cards(); //how to handle vectors
    net::TCP_Server::sendToPlayer(player_id,respond.dump());
}

////////////////////////////////reset_game//////////////////////////////////////////////////
// Doesn't work correctly at the current time.
void Game_Controller::reset_game()
{
    //get list of players
    auto& players = game_state->get_players();
    delete game_state;
    game_state = new Game_State();
    //reset the hands of the players
    for(auto& player : players)
    {
        //reset hand
        //clear and create hand
        player.second->get_hand().clear();
        std::list<ck_Cards::Cards> hand_list;
        for (unsigned int i = 0; i < 7; ++i)
        {
            ck_Cards::Cards card = game_state->get_draw_pile().get_top_card(); //get cards from draw_pile
            hand_list.push_back(card);
        }
        player.second->get_hand().push(hand_list);

        //reset has_won, players_turn
        player.second->set_has_won(false);
        player.second->set_players_turn(false);

        game_state->add_Players(player.second);
    }
    
    //broadcast_game_state();
}

////////////////////////////////////draw_card///////////////////////////////////////////////

void Game_Controller::draw_card(const Player_id& player_id)
{
    //check if one has to reshuffle
    ck_Cards::Draw_Pile& draw_pile = game_state->get_draw_pile();

    if(game_state->get_draw_pile().empty())
    {
        ck_Cards::Discard_Pile& discard_pile = game_state->get_discard_pile();

        ck_Cards::Cards top_card = discard_pile.get_top_card();
        discard_pile.shuffle();
        draw_pile.push(discard_pile.get_cards());
        discard_pile.clear();
        discard_pile.push(top_card);
    }
    ck_Cards::Cards card = draw_pile.get_top_card();

    //add to hand
    game_state->get_player(player_id)->get_hand().push(card); //maybe call this method add
}

//////////////////////////////valid_move//////////////////////////////////////////////////

//checks if card is allowed to be played
bool Game_Controller::valid_move(const ck_Cards::Cards& card)
{
    ck_Cards::Cards top_card = game_state->get_discard_pile().back();
    ck_Cards::Card top_card_object = ck_Cards::Deck::get(top_card);
    ck_Cards::Card card_object = ck_Cards::Deck::get(card);
    if(card_object.action == ck_Cards::Action::WILD || card_object.action == ck_Cards::Action::WILD_DRAW4)
        return true;
    else if(card_object.color == game_state->get_color_to_be_matched())
        return true;
    else if((card_object.value == top_card_object.value) && (card_object.action == top_card_object.action))
        return true;
    else
        return false;
}

///////////////////////////////effect_of_card/////////////////////////////////////////////////

void Game_Controller::effect_of_card(const Player_id& player_id, ck_Cards::Cards card)
{
    ck_Cards::Card card_object = ck_Cards::Deck::get(card);

    if(card_object.action == ck_Cards::Action::NONE)
    {
        //switch player
        switch_player(player_id);

        //set color_to_be_matched
        game_state->set_color_to_be_matched(card_object.color);
        broadcast_game_state();
    }
    if(card_object.action == ck_Cards::Action::DRAW2)
    {
        //set color_to_be_matched
        game_state->set_color_to_be_matched(card_object.color);

        Player_id next_player_id = get_next_player(player_id);
        //add two cards to other players hand
        draw_card(next_player_id);
        draw_card(next_player_id);

        //send hand to player
        send_hand(next_player_id);
        //set current_player to next player
        switch_player(player_id);

        broadcast_game_state();
    }
    if(card_object.action == ck_Cards::Action::WILD_DRAW4)
    {
        //ask for color
        nlohmann::json request;
        request["type"] = Respond_Type::SELECT_COLOR;
        net::TCP_Server::sendToPlayer(player_id,request.dump());

        Player_id next_player_id = get_next_player(player_id);

        //add four cards to other players hand
        draw_card(next_player_id);
        draw_card(next_player_id);
        draw_card(next_player_id);
        draw_card(next_player_id);

        //send hand
        send_hand(next_player_id);
    }
    if(card_object.action == ck_Cards::Action::WILD)
    {
        //ask for color
        nlohmann::json request;
        request["type"] = Respond_Type::SELECT_COLOR;
        net::TCP_Server::sendToPlayer(player_id,request.dump());
    }
    if(card_object.action == ck_Cards::Action::SKIP)
    {
        //set next player
        Player_id next_player_id = get_next_player(player_id);
        switch_player(next_player_id);

        //set color_to_be_matched
        game_state->set_color_to_be_matched(card_object.color);
        broadcast_game_state();
    }
    if(card_object.action == ck_Cards::Action::REVERSE)
    {
        
        std::reverse(game_state->get_players().begin(), game_state->get_players().end());

        //change current_player
        switch_player(player_id);

        //set color_to_be_matched
        game_state->set_color_to_be_matched(card_object.color);
        broadcast_game_state();
    }
}

///////////////////////next_player/////////////////////////////////////////////////////////
Player_id Game_Controller::get_next_player(const Player_id& player_id)
{
    //using std::vector<std::pair<const Player_id, Player*> >::iterator;
    std::vector<std::pair<Player_id, Player*> > players = game_state->get_players();
    //return pair with player_id as first value
    auto find = [&players](Player_id player_id) {for(auto elem = players.begin(); elem != players.end(); ++elem) if(elem->first == player_id) return elem; throw new ckException("Error: Player not found");};
    std::vector<std::pair<Player_id, Player*> >::iterator it = find(player_id);

    //lambda function checking if player_id is last element in map
    auto is_last = [&players] (std::vector<std::pair<Player_id, Player*> >::iterator iter) {if(++iter == players.end()) {return true;} return false;};

    //periodic increment skip player which have won
    while(true)
    {
        if(is_last(it))
        {
            it = players.begin();
            //auto next_player = it;
            if(!(it->second->get_has_won()))
                return it->first;
        }
        else
        {
            ++it;
            if(!(it->second->get_has_won()))
                return it->first;
        }

    }

}

////////////////////////////switch_player//////////////////////////////////
void Game_Controller::switch_player(const Player_id& player_id)
{
    Player_id next_player_id = get_next_player(player_id);
    Player* next_player = game_state->get_player(next_player_id);
    next_player->set_players_turn(true);
    game_state->set_current_player(next_player->get_player_id());
}

Game_State* Game_Controller::get_game_state()
{
    return game_state;
}
