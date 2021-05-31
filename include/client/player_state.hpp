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
	Player_State(bool test);// = testing state
	Player_State(Player_id id,std::string player_name, size_t nof_players);// = testing state
	~Player_State();

	void set_top_discard(ck_Cards::Cards);
	void set_to_be_matched(ck_Cards::Color);
	void set_players_id(Player_id);
	void set_current_player(Player_id);
	void set_players_turn(bool); 
	void set_player_won(bool);
	void set_winner(Player_id); 
	void set_number_of_cards(Player_id, size_t);
	void set_hand(ck_Cards::Hand* /*hand_*/);
	void update_hand(); //also update number of cards
	void change_play_direction(); // for reverse
	void set_all_player_names(std::vector<std::string>);
	void set_is_waiting(bool);
	void set_uno(bool);
	void set_match_colour(bool); 
	void set_is_waiting_for_start(bool);


	ck_Cards::Cards* get_top_discard();
	ck_Cards::Color get_to_be_matched() const;
	ck_Cards::Hand* get_hand() const;
	//int get_nof_cards() const;
	bool get_players_turn() const;
	Player_id get_this_player() const;
	Player_id get_current_player() const;
	Player_id get_winner() const;
	bool has_player_won() const;
	bool is_waiting() const;
	bool has_player_quit() const;
	bool get_play_direction() const;
	std::string get_player_name() const;
	std::string get_name_of_playerid(Player_id) const;
	bool is_waiting_for_start() const;
	size_t get_number_of_cards(Player_id) const;
	bool get_uno() const;
	bool get_match_colour() const;
	std::vector<Player_id>* get_id_vec();



private:
	ck_Cards::Cards top_discard; // top card of discard pile. Needs to be shown to player
	bool discard_empty;
	ck_Cards::Hand* hand;	
	ck_Cards::Color to_be_matched;
	bool match_colour; // True if okayer has to play a specific colour
	// TODO: Change to number_of_cards(PLayerID)
	bool players_turn;
	bool play_direction;
	Player_id this_player; // ID of player associated with this PlayerState.
	Player_id current_Player; // ID of player whose turn it is.
	Player_id winner; // ID of player that won.
	bool player_won; // has a player wone
	//true if player is waiting for the game to start, 0 if the game is already ongoing
	bool player_waiting;
	bool waiting_for_start;
	bool player_quit; // Exited the game without winning
	bool uno;
	std::vector<Player_id> player_ids;
	std::vector<std::string> all_Player_Names;
	std::vector<size_t> number_of_cards;
};

#endif /* PLAYER_STATE_HPP */
