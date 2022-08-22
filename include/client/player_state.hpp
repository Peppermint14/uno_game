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
	~Player_State();

	//Setters
	void set_top_discard(ck_Cards::Cards); // Set's the top discard card (Has to)
	void set_to_be_matched(ck_Cards::Color);
	void set_this_player(Player_id);
	void set_current_player(Player_id);
	void set_players_turn(bool); 
	void set_player_won(bool);
	void set_winner(Player_id); 
	void set_number_of_cards(Player_id, size_t);
	void set_hand(ck_Cards::Hand* /*hand_*/);
	void update_hand(); //also update number of cards
	void change_play_direction(); // for reverse
	void set_all_player_names(std::vector<std::string>);
	void set_uno(bool);
	void set_match_colour(bool); 
	void set_is_waiting_for_start(bool);
	void set_game_over(bool);
	void set_n_players(int n);
	void set_id_vec(std::vector<Player_id>& /*player_ids_*/);

	// getters
	ck_Cards::Cards* get_top_discard();
	ck_Cards::Color get_to_be_matched() const;
	ck_Cards::Hand* get_hand() const;
	bool get_players_turn() const;
	Player_id get_this_player() const;
	Player_id get_current_player() const;
	Player_id get_winner() const;
	bool has_player_won() const;
	bool is_waiting() const;
	bool has_player_quit() const;
	bool get_play_direction() const;
	bool get_game_over() const;
	std::string get_player_name() const;
	std::string get_name_of_playerid(Player_id) const;
	bool is_waiting_for_start() const;
	size_t get_number_of_cards(Player_id) const;
	bool get_uno() const;
	bool get_match_colour() const;
	std::vector<Player_id>* get_id_vec();
	int get_n_players() const;


private:
	int n_player_in_game = 0; 
	ck_Cards::Cards top_discard; // Top card of discard pile. Playable cards can be derived from this card.
	bool discard_empty;  // 1 <=> discard pile empty. Used at the beginning to display an empty pile
	ck_Cards::Hand* hand;	// Cards held by the player. Will be displayed by GUI.
	ck_Cards::Color to_be_matched; // Colour which has to be matched by the player. (After a wild card)
	bool match_colour; // True if okayer has to play a specific colour.
	bool players_turn; // 1 <=> the current player it this player.
	bool play_direction; // Direction of GUI Arrow. 1 <=> Downwards arrow, 0 <=> upwards arrow.
	Player_id this_player; // ID of player associated with this PlayerState.
	Player_id current_Player; // ID of player whose turn it is.
	Player_id winner; // ID of player that won.
	bool player_won; // has a player won
	bool game_over; // Game is over everybody won except 1 player.
	bool waiting_for_start; //true if player is waiting for the game to start, false if the game is already ongoing
	bool player_quit; // Exited the game without winning.
	bool uno;	// True <=> A player has UNO.
	std::vector<Player_id> player_ids; // Holds Player IDs.
	std::vector<std::string> all_Player_Names; // Holds Player Names.
	std::vector<size_t> number_of_cards; // Holds number of cards corresponding to player IDs.
};

#endif /* PLAYER_STATE_HPP */
