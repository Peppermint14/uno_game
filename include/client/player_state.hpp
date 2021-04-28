#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include "../common/common.hpp"
#include "../common/cards.hpp"

// TODO: Values set for development purposes
//includes all information such that GUI can render the board
class Player_State
{

public:
	Player_State();// = default; // default constructor
	~Player_State();
	void set_players_turn(bool); 
	void set_player_won(bool); 
	void set_number_of_cards(size_t);
	void set_hand(ck_Cards::Hand* /*hand_*/);
	void update_hand(); //also update number of cards
	void change_play_direction(); // for reverse
	void set_all_player_names();
	ck_Cards::Hand* get_hand() const;
	int get_nof_cards() const;
	bool get_players_turn() const;
	int get_player_id() const;
	bool has_player_won() const;
	bool is_waiting() const;
	std::string get_player_name() const;



private:
	ck_Cards::Hand* hand;
	size_t number_of_cards;
	bool players_turn;
	bool play_direction;
	int player_id;
	bool player_won;
	bool player_waiting;
	std::vector<std::string> all_Player_Names;
};

#endif /* PLAYER_STATE_HPP */
