#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "../common/common.hpp"
#include "game_state.hpp"
#include "../common/cards.hpp"
#include "tcp_server.hpp"
#include "player.hpp"
#include <iterator>

class Game_Controller {
public:
    Game_Controller(); //constructor, initialize game

    void eval_request(const Player_id& /*player_id*/, const std::string& /*msg*/); //evaluate requests and send responses

    //void initialize_game(); //initialize game
    //add player to game_state
    void add_new_player(const Player_id& /*player_id*/, const std::string& player_name);

    //draw number_of_cards cards and add to players hand
    void draw_card(const Player_id& /*player_id*/);
    void send_hand(const Player_id& /*player_id*/);
    //check if played card can be played
    bool valid_move(const ck_Cards::Cards& /*card*/);

    //get the Player id of the next player in players vector
    Player_id get_next_player(const Player_id& /*player_id*/);
    //set current_player to the next player in players vector
    void switch_player(const Player_id& /*player_id*/);

    //updates game_state according to played card
    void effect_of_card(const Player_id& /*player_id*/, const ck_Cards::Cards /*card*/);

    //constructs a new game_state, with new cards
    void reset_game();

    void broadcast_game_state() const;

    //just for testing purposes
    Game_State* get_game_state();

private:
    Game_State* game_state;
};
#endif /* GAME_CONTROLLER_HPP */


