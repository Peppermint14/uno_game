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
	void set_top_discard(ck_Cards::Cards);
	void set_players_turn(bool); 
	void set_player_won(bool); 
	void set_number_of_cards(size_t);
	size_t get_number_of_cards();
	void set_hand(ck_Cards::Hand* /*hand_*/);
	void update_hand(); //also update number of cards
	void change_play_direction(); // for reverse
	void set_all_player_names();
	ck_Cards::Cards* get_top_discard();
	ck_Cards::Hand* get_hand() const;
	int get_nof_cards() const;
	bool get_players_turn() const;
	Player_id get_current_player() const;
	bool has_player_won() const;
	bool is_waiting() const;
	bool has_player_quit() const;
	std::string get_player_name() const;



private:
	ck_Cards::Cards top_discard; // top card of discard pile. Needs to be shown to player
	bool discard_empty;
	ck_Cards::Hand* hand;		
	size_t number_of_cards;
	bool players_turn;
	bool play_direction;
	Player_id current_Player;
	bool player_won;
	bool player_waiting;
	bool player_quit; // Exited the game without winning
	std::vector<std::string> all_Player_Names;
};

#endif /* PLAYER_STATE_HPP */
