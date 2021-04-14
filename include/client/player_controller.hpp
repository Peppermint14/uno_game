#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "../common/common.hpp"

#include "UI/GameWindow.hpp"
#include "UI/ConnectionPanel.hpp"
#include "UI/MainGamePanel.hpp"
#include "../server/game_state.hpp"


class player_controller {

public:
    static void init(GameWindow* gameWindow);

    static void connectToServer();
    static void updateGameState(game_state* newGameState);
    static void startGame();
    static void drawCard();
    static void fold();
    //static void playCard(card* cardToPlay);

    static wxEvtHandler* getMainThreadEventHandler();
    static void showError(const std::string& title, const std::string& message);
    static void showStatus(const std::string& message);
    static void showNewRoundMessage(game_state* oldGameState, game_state* newGameState);
    static void showGameOverMessage();

private:
    static GameWindow* _gameWindow;
    static ConnectionPanel* _connectionPanel;
    static MainGamePanel* _mainGamePanel;

    static Player* _me;
    static game_state* _currentGameState;

};

#endif /* PLAYER_CONTROLLER_HPP */