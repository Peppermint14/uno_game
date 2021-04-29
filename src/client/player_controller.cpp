// Copied from Lama example Project

#include "../../include/client/player_controller.hpp"
#include "../../include/client/UI/MainGamePanel.hpp"

// #include "../common/network/requests/join_game_request.h"
// #include "../common/network/requests/start_game_request.h"
// #include "../common/network/requests/draw_card_request.h"
// #include "../common/network/requests/fold_request.h"
// #include "../common/network/requests/play_card_request.h"
// #include "network/ClientNetworkManager.h"


// initialize static members
GameWindow* player_controller::_gameWindow = nullptr;
ConnectionPanel* player_controller::_connectionPanel = nullptr;
MainGamePanel* player_controller::_mainGamePanel = nullptr;

Player* player_controller::_me = nullptr;
Player_State* player_controller::_currentPlayerState = nullptr;


Player_State test_state = Player_State();



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
    //send_request that 'colour' was picked
}

void player_controller::connectToServer() {

    // get values form UI input fields
    wxString inputServerAddress = player_controller::_connectionPanel->getServerAddress().Trim();
    wxString inputServerPort = player_controller::_connectionPanel->getServerPort().Trim();
    wxString inputPlayerName = player_controller::_connectionPanel->getPlayerName().Trim();

    updateGameState(&test_state);    
    _gameWindow->showPanel(_mainGamePanel);
    
    //PickColour();

    // check that all values were provided
    // if(inputServerAddress.IsEmpty()) {
    //     player_controller::showError("Input error", "Please provide the server's address");
    //     return;
    // }
    // if(inputServerPort.IsEmpty()) {
    //     player_controller::showError("Input error", "Please provide the server's port number");
    //     return;
    // }
    // if(inputPlayerName.IsEmpty()) {
    //     player_controller::showError("Input error", "Please enter your desired player name");
    //     return;
    // }

    // convert host from wxString to std::string
    // std::string host = inputServerAddress.ToStdString();

    // convert port from wxString to uint16_t
    // unsigned long portAsLong;
    // if(!inputServerPort.ToULong(&portAsLong) || portAsLong > 65535) {
    //     player_controller::showError("Connection error", "Invalid port");
    //     return;
    // }
    // uint16_t port = (uint16_t) portAsLong;

    // //convert player name from wxString to std::string
    // std::string playerName = inputPlayerName.ToStdString();

    // //connect to network
    // ClientNetworkManager::init(host, port);

    // //send request to join game
    // player_controller::_me = new player(playerName);
    // join_game_request request = join_game_request(player_controller::_me->get_id(), player_controller::_me->get_player_name());
    // ClientNetworkManager::sendRequest(request);

}

//possible requesttypes: NEW_PLAYER, START_GAME, PLAY_REQUEST, DRAW_REQUEST,EXIT_REQUEST
void player_controller::send_request(Request_Type request_type,ck_Cards::Cards card)
{
	Player_id id = _me->get_player_id();
	nlohmann::json request;
	request["id"] = id;
	request["type"] = request_type;
	
	if(request_type == Request_Type::PLAY_REQUEST){
		request["card"] = card;
	}
	//-> send this: request.dump() with tcp to server
}

void player_controller::eval_response(const std::string& msg)
{
	nlohmann::json response = nlohmann::json::parse(msg);
	Respond_Type response_type = response["type"];
	switch(response_type)
	{
		case Respond_Type::SUCCESFUL_CONNECTION:
			{
				_me->set_is_active(true);
				break;
			}
		case Respond_Type::SEND_HAND:
			{
				//sendet hand vo me (charte ids)
				//ck_Cards::Hand hand = response["hand"];
				break;
			}
		case Respond_Type::GAME_UPDATE:
			{
				/*
				//update number of cards of all players
				//liste mit zweier listen, welche player id und number of cards von der jeweiligen person enthalten
				//"players": "Player_id": , number_of_cars_],[......
				nlohmann::json::array pla = response["players"]
				for(player:players){
					set_number_cards_player(player.first,player.second);
				}
				*/
				//update whos turn it is
				Player_id current_id= response["current_player"];
				set_current_player(current_id);
				
				//update, which color has to be played
				ck_Cards::Color color = response["color_to_be_matched"];
				set_color(color);
				
				//update, which card is on top of the discard Pile
				ck_Cards::Cards top_card = response["top_card"];
				set_top_card_discardp(top_card);

				break;
			}
		case Respond_Type::ERROR_:
			{
				std::string message = response["msg"];
				set_error_message(message);

				break;
			}
	}

}

void player_controller::updateGameState(Player_State* newGameState) {

    
    // the existing game state is now old
    Player_State* oldPlayerState = player_controller::_currentPlayerState;

    // save the new game state as our current game state
    player_controller::_currentPlayerState = newGameState;
/*
    if(oldGameState != nullptr) {

        // check if a new round started, and display message accordingly
        if(oldGameState->get_round_number() > 0 && oldGameState->get_round_number() < newGameState->get_round_number()) {
            player_controller::showNewRoundMessage(oldGameState, newGameState);
        }

        // delete the old game state, we don't need it anymore
        delete oldGameState;
    }

    if(player_controller::_currentGameState->is_finished()) {
        player_controller::showGameOverMessage();
    }
*/
    // make sure we are showing the main game panel in the window (if we are already showing it, nothing will happen)
    player_controller::_gameWindow->showPanel(player_controller::_mainGamePanel);

    // command the main game panel to rebuild itself, based on the new game state
    player_controller::_mainGamePanel->buildPlayerState(_currentPlayerState, player_controller::_me);
    
}


void player_controller::startGame() {
    // start_game_request request = start_game_request(player_controller::_currentGameState->get_id(), player_controller::_me->get_id());
    // ClientNetworkManager::sendRequest(request);
}


void player_controller::drawCard() {

    // Send request
    //TCP_client::requestDrawCard();

    // Update Cards
    //MainGamePanel::redrawCards();



    // draw_card_request request = draw_card_request(player_controller::_currentGameState->get_id(), player_controller::_me->get_id());
    // ClientNetworkManager::sendRequest(request);
}


void player_controller::fold() {
    // fold_request request = fold_request(player_controller::_currentGameState->get_id(), player_controller::_me->get_id());
    // ClientNetworkManager::sendRequest(request);
}


void player_controller::playCard(const ck_Cards::Cards* cardToPlay) {
    // play_card_request request = play_card_request(player_controller::_currentGameState->get_id(), player_controller::_me->get_id(), cardToPlay->get_id());
    // ClientNetworkManager::sendRequest(request);
    std::cout << "PLAYING CARD: " << uint32_t(*cardToPlay) <<  std::endl;
}


wxEvtHandler* player_controller::getMainThreadEventHandler() {
    // return player_controller::_gameWindow->GetEventHandler();
}


void player_controller::showError(const std::string& title, const std::string& message) {
    // wxMessageBox(message, title, wxICON_ERROR);
}


void player_controller::showStatus(const std::string& message) {
    // player_controller::_gameWindow->setStatus(message);
}


void player_controller::showNewRoundMessage(Player_State* oldGameState, Player_State* newGameState) {
    /*
    std::string title = "Round Completed";
    std::string message = "The players gained the following minus points:\n";
    std::string buttonLabel = "Start next round";

    // add the point differences of all players to the messages
    for(int i = 0; i < oldGameState->get_players().size(); i++) {

        player* oldPlayerState = oldGameState->get_players().at(i);
        player* newPlayerState = newGameState->get_players().at(i);

        int scoreDelta = newPlayerState->get_score() - oldPlayerState->get_score();
        std::string scoreText = std::to_string(scoreDelta);
        if(scoreDelta > 0) {
            scoreText = "+" + scoreText;
        }

        std::string playerName = newPlayerState->get_player_name();
        if(newPlayerState->get_id() == player_controller::_me->get_id()) {
            playerName = "You";
        }
        message += "\n" + playerName + ":     " + scoreText;
    }

    wxMessageDialog dialogBox = wxMessageDialog(nullptr, message, title, wxICON_NONE);
    dialogBox.SetOKLabel(wxMessageDialog::ButtonLabel(buttonLabel));
    dialogBox.ShowModal();
    */
}


void player_controller::showGameOverMessage() {
    
    /*
    std::string title = "Game Over!";
    std::string message = "Final score:\n";
    std::string buttonLabel = "Close Game";

    // sort players by score
    std::vector<player*> players = player_controller::_currentGameState->get_players();
    std::sort(players.begin(), players.end(), [](const player* a, const player* b) -> bool {
        return a->get_score() < b->get_score();
    });

    // list all players
    for(int i = 0; i < players.size(); i++) {

        player* playerState = players.at(i);
        std::string scoreText = std::to_string(playerState->get_score());

        // first entry is the winner
        std::string winnerText = "";
        if(i == 0) {
            winnerText = "     Winner!";
        }

        std::string playerName = playerState->get_player_name();
        if(playerState->get_id() == player_controller::_me->get_id()) {
            playerName = "You";

            if(i == 0) {
                winnerText = "     You won!!!";
            }
        }
        message += "\n" + playerName + ":     " + scoreText + winnerText;
    }

    wxMessageDialog dialogBox = wxMessageDialog(nullptr, message, title, wxICON_NONE);
    dialogBox.SetOKLabel(wxMessageDialog::ButtonLabel(buttonLabel));
    int buttonClicked = dialogBox.ShowModal();
    if(buttonClicked == wxID_OK) {
        player_controller::_gameWindow->Close();
    }
    */
}
void player_controller::set_number_cards_player(Player_id id, int number_cards){
	players_number_of_cards[(int)id] = number_cards;
}
int player_controller::get_number_cards_player(Player_id id){
	int number_of_cards = players_number_of_cards[(int)id];
	return number_of_cards;
}

void player_controller::set_current_player(Player_id id){
	current_player = id;
}
Player_id player_controller::get_current_player(){
	return current_player;
}

void player_controller::set_color(ck_Cards::Color color){
	color_to_be_played = color;
}
ck_Cards::Color player_controller::get_color(){
	return color_to_be_played;
}


void player_controller::set_top_card_discardp(ck_Cards::Cards top){
	top_card_on_discard = top;
}
ck_Cards::Cards player_controller::get_top_card_discardp(){
	return top_card_on_discard;
}

void player_controller::set_error_message(std::string message){
	error_occured = true;
	error_message = message;
}
void player_controller::error_read(){
	error_occured = false;
}
std::string player_controller::get_error_message(){
	return error_message;
}
