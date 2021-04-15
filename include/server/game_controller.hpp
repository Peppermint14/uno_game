#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "../common/common.hpp"
#include "game_state.hpp"
#include "../common/cards.hpp"
#include "tcp_server.hpp"

class Game_Controller {
public:
    Game_Controller(); //constructor, initialize game

    void eval_request(Player_id& /*player_id*/, std::string& /*msg*/); //evaluate requests and send responses

    //void initialize_game(); //initialize game
    void add_new_player(Player_id& /*_player_id*/);

    void update_game_state();

private:
    Game_State* game_state;
};
#endif /* GAME_CONTROLLER_HPP */


