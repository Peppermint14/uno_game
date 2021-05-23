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
    // player_controller* get_ctrl(){return this;};
    player_controller();
    void init(GameWindow* gameWindow);
    static void connectToServer();
    static void eval_response(const std::string& msg);
    static void updatePlayerState(Player_State* newPlayerState);
    static void startGame();
    static void drawCard();
    static void fold();
    static void PickColour();
    static void playCard(const ck_Cards::Cards* cardToPlay);
    static void join(std::string);
    static void exit();


    static wxEvtHandler* getMainThreadEventHandler();
    static void showError(const std::string& title, const std::string& message);
    static void showStatus(const std::string& message);
    static void showNewRoundMessage(Player_State* oldPlayerState, Player_State* newPlayerState);
    static void showGameOverMessage();

    void set_number_cards_player(std::list<std::pair<Player_id, int>>);
    //in: Id of the player, of which you want to know the number of cards
    //out: integer telling how many cards the corresponding player has
    std::list<std::pair<Player_id, int>> get_number_cards_player();
    
    // void set_current_player(Player_id);
    // Player_id get_current_player();

    void set_color(ck_Cards::Color);
    ck_Cards::Color get_color();

    void set_top_card_discardp(ck_Cards::Cards);
    ck_Cards::Cards get_top_card_discardp();

    void set_error_message(std::string);
    void error_read(); //-> error_message is not accurate anymore
    std::string get_error_message();

private:
    static GameWindow* _gameWindow;
    static ConnectionPanel* _connectionPanel;
    static MainGamePanel* _mainGamePanel;
    // static player_controller* _this_ctrl;
    //at position i is the number of cards that player i has stored (position 0 is zero (player zero is error)
    std::list<std::pair<Player_id, int>> players_number_of_cards;
    static Player* _me;
    Player_id current_player;
    static Player_State* _currentPlayerState;
    ck_Cards::Color color_to_be_played; 
    ck_Cards::Cards top_card_on_discard;
     
    //ev gibt es bessere Möglichkeit errors zu handeln??
    bool error_occured;
    std::string error_message;

};

#endif /* PLAYER_CONTROLLER_HPP */
