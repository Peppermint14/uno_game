#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "../common/common.hpp"
#include "../common/cards.hpp"

#include "UI/GameWindow.hpp"
#include "UI/ConnectionPanel.hpp"
#include "UI/MainGamePanel.hpp"
#include "player_state.hpp"


class player_controller {

public:
    static void init(GameWindow* gameWindow);

    static void connectToServer();
    static void updateGameState(Player_State* newGameState);
    static void startGame();
    static void drawCard();
    static void fold();
    static void PickColour();
    static void playCard(const ck_Cards::Cards* cardToPlay);
    

    static wxEvtHandler* getMainThreadEventHandler();
    static void showError(const std::string& title, const std::string& message);
    static void showStatus(const std::string& message);
    static void showNewRoundMessage(Player_State* oldGameState, Player_State* newGameState);
    static void showGameOverMessage();

private:
    static GameWindow* _gameWindow;
    static ConnectionPanel* _connectionPanel;
    static MainGamePanel* _mainGamePanel;

    static Player* _me;
    static Player_State* _currentPlayerState;

};

#endif /* PLAYER_CONTROLLER_HPP */