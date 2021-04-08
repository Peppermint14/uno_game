#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "../common/common.hpp"
#include "game_state.hpp"

class Game_Controller {
public:
    Game_Controller();

    void eval_request(Player_id, std::string&); //evaluate requests and send responses

    void initialize_game(); //initialize game

    void update_game_state();

private:
    game_state* game_state_;
};
#endif /* GAME_CONTROLLER_HPP */


