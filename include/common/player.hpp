#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../common/common.hpp" //retrieve Player_id of type enum class
#include "../client/player_state.hpp"

class Player
{
public:
	Player(); //constructor
	void set_is_active(bool);

private:

	Player_id player_id_; //unique player id
	Player_State player_state_;
	bool is_active; //if player has exited set is_active to false
	
};

#endif /* PLAYER_HPP */
