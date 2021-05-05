#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../common/common.hpp" //retrieve Player_id of type enum class

#include "../client/player_state.hpp"

#include "../common/cards.hpp"
#include <string>


class Player
{
public:
	Player(Player_id /*player_id_*/, bool /*is_active_*/); //constructor
	void set_is_active(bool);
	Player_id get_player_id() const;
	Player_State* get_player_state() const;
	bool get_is_active() const;

private:

	Player_id player_id; //unique player id
	Player_State* player_state;
	bool is_active; //if player has exited set is_active to false

	Player(const Player_id& /*player_id_*/, bool /*is_active_*/, const std::string& /*player_name_*/); //constructor
	void set_is_active(bool);
	void set_hand(ck_Cards::Hand* /*hand_*/); //also set number of cards
	void set_has_won(bool /*has_won_*/);
	bool get_has_won() const;
	const size_t number_of_cards() const;
	const Player_id& get_player_id() const;
	const std::string& get_player_name() const;
	const bool& get_is_active() const;
	ck_Cards::Hand* get_hand() const;
	void set_players_turn(bool /*players_turn_*/);

private:

	const Player_id player_id; //unique player id
	const std::string player_name;
	ck_Cards::Hand* hand;
	bool players_turn; //is this set to 0 when constructing?
	bool has_won;
	bool is_active; //if player has exited set is_active to false
};

#endif /* PLAYER_HPP */
