#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "../common/common.hpp"
#include "game_state.hpp"

class game_controller {
public:
    game_controller();

    void eval_request(Player_id, std::string&); //evaluate requests and send responses

    void init(); //initialize game_state

    void update_game_state();

private:
    game_state game_state_;
};
#endif /* GAME_CONTROLLER_HPP */


