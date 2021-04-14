#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../common/common.hpp" //retrieve Player_id of type enum class
#include "../client/player_state.hpp"

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
	
};

#endif /* PLAYER_HPP */
