#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "../common/common.hpp"
#include "game_state.hpp"
#include "../common/cards.hpp"
#include "tcp_server.hpp"
#include <iterator>

class Game_Controller {
public:
    Game_Controller(); //constructor, initialize game

    void eval_request(Player_id& /*player_id*/, std::string& /*msg*/); //evaluate requests and send responses

    //void initialize_game(); //initialize game
    //add player to game_state
    void add_new_player(Player_id& /*player_id*/, std::string& player_name);

    //draw number_of_cards cards and add to players hand
    void draw_card(Player_id& /*player_id*/);
    void send_hand(Player_id& /*player_id*/);
    //check if played card can be played
    bool valid_move(ck_Cards::Cards& /*card*/);

    Player_id get_next_player(Player_id& /*player_id*/);
    //set current_player to the next player in players map
    void switch_player(Player_id& /*player_id*/);

    //updates game_state according to played card
    void effect_of_card(Player_id& /*player_id*/, ck_Cards::Cards /*card*/);

    void broadcast_game_state() const;

private:
    Game_State* game_state;
};
#endif /* GAME_CONTROLLER_HPP */


