#include "../../include/client/player_controller.hpp"
#include "../../include/client/UI/MainGamePanel.hpp"
#include "../../include/common/cards.hpp"
#include "../../include/common/common.hpp"
#include "../../include/client/digital_UNO.hpp"


// Player_State test_state = Player_State(1);

// initialize static members
GameWindow* player_controller::_gameWindow = nullptr;
ConnectionPanel* player_controller::_connectionPanel = nullptr;
MainGamePanel* player_controller::_mainGamePanel = nullptr;

Player_State* player_controller::_currentPlayerState = new Player_State() ;
Player* player_controller::_me = new Player(_currentPlayerState);

std::list<std::pair<Player_id, int>> player_controller::players_number_of_cards = {{Player_id::NONE,0},{Player_id::NONE,0},{Player_id::NONE,0},{Player_id::NONE,0}};
ck_Cards::Color player_controller::color_to_be_played = ck_Cards::Color::NONE;
ck_Cards::Cards player_controller::top_card_on_discard = ck_Cards::Cards::BLUE_0;
Player_id player_controller::current_player = Player_id::NONE;

net::TCP_Client* _current_Client = nullptr;


void player_controller::init(GameWindow* gameWindow) {

    player_controller::_gameWindow = gameWindow;

    // Set up main panels
    player_controller::_connectionPanel = new ConnectionPanel(gameWindow);
    player_controller::_mainGamePanel = new MainGamePanel(gameWindow);

    // Hide all panels
    player_controller::_connectionPanel->Show(false);
    player_controller::_mainGamePanel->Show(false);

    // Only show connection panel at the start of the game
    player_controller::_gameWindow->showPanel(player_controller::_connectionPanel);
    
    
    // Set status bar
    player_controller::showStatus("Not connected");
    
}


void player_controller::PickColour(){

    wxString colour = _mainGamePanel->colourPicker();
}

void player_controller::connectToServer() {

    // get values form UI input fields
    wxString inputServerAddress = player_controller::_connectionPanel->getServerAddress().Trim();
    wxString inputServerPort = player_controller::_connectionPanel->getServerPort().Trim();
    wxString inputPlayerName = player_controller::_connectionPanel->getPlayerName().Trim();
   

    //check that all values were provided
    if(inputServerAddress.IsEmpty()) {
         player_controller::showError("Input error", "Please provide the server's address");
         return;
    }
    if(inputServerPort.IsEmpty()) {
         player_controller::showError("Input error", "Please provide the server's port number");
         return;
    }
    if(inputPlayerName.IsEmpty()) {
         player_controller::showError("Input error", "Please enter your desired player name");
         return;
     }
     

    //convert port from wxString to uint16_t
    unsigned long portAsLong;
    if(!inputServerPort.ToULong(&portAsLong) || portAsLong > 65535) {
        player_controller::showError("Connection error", "Invalid port");
        return;
    }
    uint16_t port = (uint16_t) portAsLong;

    // //convert player name from wxString to std::string
    std::string playerName = inputPlayerName.ToStdString();
    
    // convert host from wxString to std::string
    std::string serveraddress = inputServerAddress.ToStdString();

    player_controller::_me->set_player_name(playerName);
	
    // connect to network
    try{
	    net::TCP_Client::connect(serveraddress, port, [](const std::string _msg){
            		getMainThreadEventHandler()->CallAfter([_msg]{eval_response(_msg);});
        }); //playercontroller eval_response
    } catch(const ckException& _e){
        auto logger = Logger::get("client_main");
        logger->error(_e.what());
        return;
    }    

    updatePlayerState();
    showStatus("Connected: " + serveraddress);
    _gameWindow->showPanel(_mainGamePanel);
}

void player_controller::eval_response(const std::string& msg)
{
	nlohmann::json response = nlohmann::json::parse(msg);
	
    //id without type
    if(response.count("type") == 0){
	Player_id id = response["id"];    
        player_controller::_me->set_player_id(id);
		_currentPlayerState->set_this_player(id);
	//send player name to server
	join();
	return;
    }
    
    const size_t type = response["type"];
	Respond_Type response_type = Respond_Type(type);
	switch(response_type)
	{
		case Respond_Type::SUCCESFUL_CONNECTION:
			{
				_me->set_is_active(true);
				break;
			}
		case Respond_Type::SEND_HAND:
			{
				std::list<ck_Cards::Cards> hand_cards = response["hand"];
				ck_Cards::Hand* hand = new ck_Cards::Pile(hand_cards);
				_currentPlayerState->set_hand(hand);
				break;
			}
		case Respond_Type::SELECT_COLOR:
			{

				wxString color = player_controller::_mainGamePanel->colourPicker();
				ck_Cards::Color chosen_color = wxStr_to_Color(color);
				Player_id id = player_controller::_me->get_player_id();
        		nlohmann::json request;
        		request["id"]= id;
        		request["type"] = Request_Type::SELECTED_COLOR;
				request["color"] = chosen_color;
        		net::TCP_Client::send(request.dump());
				break;
			}
		case Respond_Type::GAME_UPDATE:
			{
				//update is waiting (is the game allready ongoing or do the players have to wait)
				Player_id current_id= response["current_player"];
				//in the time, the game hasn't started yet, the server sents Player_id::NONE as current player ID
				player_controller::_currentPlayerState->set_is_waiting_for_start(current_id == Player_id::NONE);
				//update whos turn it is
				_currentPlayerState->set_current_player(current_id);
				_currentPlayerState->set_players_turn(current_id == _me->get_player_id()); // Could coalesce into set_current_player function.
	
				//update number of cards of all players
				_currentPlayerState->set_n_players(response["players"].size());
				std::vector<std::string> all_names(4); //(4);
				std::vector<Player_id> player_id;
                                for(auto it = response["players"].begin();it<response["players"].end();it++){
                                	Player_id p_id = Player_id::NONE;
                                        std::string name = "empty";
                                        int n_cards = 0;
                                        //iterates through the triplets
                                        for(int i=0;i<3;i++){
                                        	auto player_info = it->at(i);
                                              	if(player_info.front()=="number_of_cards"){
                                             		n_cards = player_info.back();
                                          	}
                                            	else if(player_info.front()=="Player_name"){
                                            		name= player_info.back();
                                          	}
                                              	else if(player_info.front()=="Player_id"){
                                              		p_id = player_info.back();
                                              	}
                                              	else{
                                           		// should not happen
                                            	}
                             		}
                                        //all_names.push_back(name);
                                        all_names[(int)p_id-1]=name;
                                        player_id.push_back(p_id);
                                        player_controller::_currentPlayerState->set_number_of_cards(p_id,n_cards);

                                }
                                _currentPlayerState->set_all_player_names(all_names);
                                _currentPlayerState->set_id_vec(player_id);
				//update, which color has to be played
				ck_Cards::Color color = response["color_to_be_matched"];
				player_controller::set_color(color);
				
				//update, which card is on top of the discard Pile
				ck_Cards::Cards new_top_card = response["top_card"];
				ck_Cards::Cards old_top_card = *(_currentPlayerState->get_top_discard());
				_currentPlayerState->set_top_discard(new_top_card);

				if((uint32_t)new_top_card >= 84 && (uint32_t)new_top_card <= 91 && old_top_card != new_top_card) // Reverse card has been played and is new
					_currentPlayerState->change_play_direction(); // Adjusting arrow to indicate play direction
				break;
			}
		case Respond_Type::ERROR_:
			{

				std::string message = response["msg"];
				player_controller::showError("error", message);

				break;
			}
		
		case Respond_Type::UNO:
			{
				Player_id id = response["id"];
                _currentPlayerState->set_uno(true);
                return; // Prevents GUI from updating, otherwise notification are sent out twice since we sill receieve another game_update anyway
			}
		case Respond_Type::START_NEW_GAME:
			{
				player_controller::showStatus("Game over");
				_currentPlayerState->set_game_over(true);
				return; // Prevents GUI from updating, otherwise notification are sent out twice since we sill receieve another game_update anyway
			}
		
		case Respond_Type::WINS:
			{
				
				Player_id winner_id = response["id"];
				_currentPlayerState->set_player_won(true);
				_currentPlayerState->set_winner(winner_id);
				return;
			}
        default:
            std::cout << "Unexpected RESULT \n";
	}
	// make sure we are showing the main game panel in the window (if we are already showing it, nothing will happen)
   	if(!player_controller::_currentPlayerState->is_waiting_for_start()){ 
		updatePlayerState();
    	_gameWindow->showPanel(_mainGamePanel);
	}
}

void player_controller::updatePlayerState(){

    // make sure we are showing the main game panel in the window (if we are already showing it, nothing will happen)
    player_controller::_gameWindow->showPanel(player_controller::_mainGamePanel);

    // command the main game panel to rebuild itself, based on the new game state
   player_controller::_mainGamePanel->buildPlayerState(player_controller::_currentPlayerState, player_controller::_me);
    
}


void player_controller::startGame() {
	Player_id id = player_controller::_me->get_player_id();
	nlohmann::json request;
	request["id"]= id;
	request["type"] = Request_Type::START_GAME;
	net::TCP_Client::send(request.dump());
}


void player_controller::drawCard() {
	Player_id id = _me->get_player_id();
	nlohmann::json request;
	request["id"]= id;
	request["type"] = Request_Type::DRAW_REQUEST;
	net::TCP_Client::send(request.dump());
}


void player_controller::playCard(const ck_Cards::Cards* cardToPlay) {
    	Player_id id = _me->get_player_id();
	nlohmann::json request;
	request["id"] = id;
	request["type"] = Request_Type::PLAY_REQUEST;
	request["card"] = *cardToPlay;
	net::TCP_Client::send(request.dump());
}

void player_controller::exit(){
    
	Player_id id = _me->get_player_id();
	nlohmann::json request;
	request["id"]= id;
	request["type"] = Request_Type::EXIT_REQUEST;
	net::TCP_Client::send(request.dump());
	sleep(2);
}

void player_controller::join(){
	Player_id id = player_controller::_me->get_player_id();
	std::string name = player_controller::_me->get_player_name();
	nlohmann::json request;
	request["id"]= id;
	request["name"] = name;
	request["type"] = Request_Type::NEW_PLAYER;
	net::TCP_Client::send(request.dump());
}

wxEvtHandler* player_controller::getMainThreadEventHandler() {
     return player_controller::_gameWindow->GetEventHandler();
}


void player_controller::showError(const std::string& title, const std::string& message) {
    wxMessageBox(message, title, wxICON_ERROR);
}


void player_controller::showStatus(const std::string& message) {
    player_controller::_gameWindow->setStatus(message);
}


void player_controller::set_number_cards_player(std::list<std::pair<Player_id, int>> player_list){
	player_controller::players_number_of_cards  = player_list;
}
std::list<std::pair<Player_id, int>> player_controller::get_number_cards_player(){
	return player_controller::players_number_of_cards;
}

void player_controller::set_color(ck_Cards::Color color){
	player_controller::color_to_be_played = color;
}
ck_Cards::Color player_controller::get_color(){
	return player_controller::color_to_be_played;
}


ck_Cards::Cards player_controller::get_top_card_discardp(){
	return player_controller::top_card_on_discard;
}

//Takes in a wxString and returns the corresponding color
ck_Cards::Color player_controller::wxStr_to_Color(wxString color){
	if(color == "Red"){
		return ck_Cards::Color::RED;
	}
	else if(color == "Green"){
		return ck_Cards::Color::GREEN;
	}
	else if(color == "Blue"){	
		return ck_Cards::Color::BLUE;
	}
	else if(color == "Yellow"){	
		return ck_Cards::Color::YELLOW;
	}
	else{
		return ck_Cards::Color::NONE;
	}	
 }

