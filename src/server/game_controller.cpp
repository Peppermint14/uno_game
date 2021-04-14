#include "../../include/server/game_controller.hpp"

//constructor, constructs game_state
Game_Controller::Game_Controller()
{
    //create deck
    //draw_pile = deck at initialization
    std::list<ck_Cards::Cards> draw_cards(108);
    for(ck_Cards::Cards card = ck_Cards::Cards::BLUE_0; card != ck_Cards::Cards::WILD_DRAW4_D; ++card)
        draw_cards.push_back(card);

    draw_cards.push_back(ck_Cards::Cards::WILD_DRAW4_D);
    ck_Cards::Draw_Pile* draw_pile = new ck_Cards::Pile(draw_cards);
    //reshuffle draw_pile
    draw_pile->shuffle();
    //retrieve top card
    ck_Cards::Cards top_card = draw_pile->get_top_card();

    while(ck_Cards::Deck::get(top_card).action != ck_Cards::Action::NONE)
    {
        draw_pile->push(top_card);
        top_card = draw_pile->get_top_card();
    }
    std::list<ck_Cards::Cards> discard_cards;
    discard_cards.push_back(top_card);

    ck_Cards::Discard_Pile* discard_pile = new ck_Cards::Pile(discard_cards);
    game_state = new Game_State(draw_pile, discard_pile);
}

void Game_Controller::eval_request(Player_id player_id, std::string& msg)
{
    nlohmann::json request = nlohmann::json::parse(msg);
    Request_Type request_type = request["type"];
    switch (request_type)
    {
        case Request_Type::NEW_PLAYER:
	{
            Player_id player_id = request["id"]; //retrieve player id
            add_new_player(player_id);
            break;
	}
        case Request_Type::START_GAME:
	{
            break;
	}
        case Request_Type::PLAY_REQUEST:
	{
            break;
	}
        case Request_Type::DRAW_REQUEST:
	{
            break;
	}
        case Request_Type::EXIT_REQUEST:
	{
            break;
	}
    }
}

void Game_Controller::add_new_player(Player_id _player_id) {
    //TODO: check if there are already four players playing.

    //retrieve hand
    std::list<ck_Cards::Cards> hand_list(7);
    for (unsigned int i = 0; i < 7; ++i)
    {
        ck_Cards::Cards card = game_state->get_discard_pile()->get_top_card(); //get cards from top card
        hand_list.push_back(card);
    }
    ck_Cards::Hand* hand = new ck_Cards::Hand(hand_list);

    //construct a new player
    Player* player = new Player(_player_id, true);
    player->get_player_state()->set_hand(hand);

    //add_player to player list of game_state
    game_state->add_Players(player);

    //send Player_id to player
    nlohmann::json respond1;
    respond1["type"] = Respond_Type::SUCCESFUL_CONNECTION;
    respond1["id"] = _player_id;
    net::TCP_Server::sendToPlayer(_player_id,respond1.dump());

    //send Hand to player
    nlohmann::json respond2;
    respond2["type"] = Respond_Type::SEND_CARDS;
    respond2["cards"] = hand->get_cards();
    net::TCP_Server::sendToPlayer(_player_id,respond2.dump());

    //broadcast game_update
    nlohmann::json respond3;
    respond3["type"] = Respond_Type::GAME_UPDATE;
    respond3["players"] = "player";
    respond3["current_player"] = game_state->get_current_player();
    respond3["color_to_be_matched"] = game_state->get_color_to_be_matched();
    respond3["top_card"] = game_state->get_discard_pile()->front();
    net::TCP_Server::broadcast(respond3);
}

