#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "../common/common.hpp"
#include "../common/cards.hpp"
#include "tcp_client.hpp"
#include "UI/GameWindow.hpp"
#include "UI/ConnectionPanel.hpp"
#include "UI/MainGamePanel.hpp"
#include "player_state.hpp"



class player_controller {

public:

    static void init(GameWindow* gameWindow);
    //processes all the information from the connection panel and calls the TCCP_Clpient connect function
    static void connectToServer();
    //handles all the responses from the server
    static void eval_response(const std::string& msg);
    //updates the graphical interface
    static void updatePlayerState();
    //sends startGame-request to server 
    static void startGame();
    //sends drawCard to server
    static void drawCard();
    static void fold();
    static void PickColour();
    
    //sends request to server, that the client wants to play the card cardToPlay
    static void playCard(const ck_Cards::Cards* cardToPlay);

    // will be called right after receiving the Id from the server 
    // sends the player name with the ID of the player to the server, to inform the server about the name
    static void join();
    static void exit();


    static wxEvtHandler* getMainThreadEventHandler();
    static void showError(const std::string& title, const std::string& message);
    static void showStatus(const std::string& message);

    static void set_number_cards_player(std::list<std::pair<Player_id, int>>);
    //in: Id of the player, of which you want to know the number of cards
    //out: integer telling how many cards the corresponding player has
    static std::list<std::pair<Player_id, int>> get_number_cards_player();

    static void set_color(ck_Cards::Color);
    static ck_Cards::Color get_color();

    static ck_Cards::Cards get_top_card_discardp();
    //helper function used to convert the wxString, which is returned when a player choses a color, to a value of type ck_Cards::Color 
    static ck_Cards::Color wxStr_to_Color(wxString color);
//private:
    static GameWindow* _gameWindow ;
    static ConnectionPanel* _connectionPanel;
    static MainGamePanel* _mainGamePanel;
    //at position i is the number of cards that player i has stored (position 0 is zero (player zero is error)
    static std::list<std::pair<Player_id, int>> players_number_of_cards;
    static Player* _me;
    //Player ID of player whose turn it is at the moment
    static Player_id current_player;
    static Player_State* _currentPlayerState;
    static ck_Cards::Color color_to_be_played; 
    static ck_Cards::Cards top_card_on_discard;
     
    
};

#endif /* PLAYER_CONTROLLER_HPP */
