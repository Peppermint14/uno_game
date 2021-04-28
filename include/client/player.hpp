#ifndef PLAYER_CLIENT_HPP
#define PLAYER_CLIENT_HPP

#include "../common/common.hpp" //retrieve Player_id of type enum class
#include "../client/player_state.hpp"

class Player
{
public:
	Player(Player_id /*player_id_*/, bool /*is_active_*/); //constructor
	void set_is_active(bool);
	Player_id get_player_id() const;
	std::string get_player_name() const;
	Player_State* get_player_state() const;
	bool get_is_active() const;
	bool has_won() const;
	bool is_waiting() const;

private:

	Player_id player_id; //unique player id
	std::string player_name;
	Player_State* player_state;
	bool is_active = 0; //if player has exited set is_active to false
	bool _has_won = 1;
	bool _is_waiting = 0; // if the game hasn't started yet
	
};

#endif /* PLAYER_CLIENT_HPP */
