#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include "../common/common.hpp"
#include "../common/cards.hpp"

//includes all information such that GUI can render board
class Player_State
{

public:
	Player_State() = default; // default constructor
	void set_players_turn(bool); 
	void set_player_won(bool); 
	void set_number_of_cards(size_t);
	void set_hand(ck_Cards::Hand* /*hand_*/);
	void update_hand(); //also update number of cards
	ck_Cards::Hand* get_hand() const;


private:
	ck_Cards::Hand* hand;
	size_t number_of_cards;
	bool players_turn;
	bool has_won;
};

#endif /* PLAYER_STATE_HPP */
