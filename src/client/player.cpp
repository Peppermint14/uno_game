#include "../../include/client/player.hpp"


Player::Player(Player_id player_id_, std::string name_, bool is_active_)
{
	player_id = player_id_;
	name = name_;
	is_active = is_active_;
	player_state = new Player_state();
}

void Player::set_is_active(bool active)
{
	is_active = active; 	
}

Player_id Player::get_player_id() const
{
	return player_id;
}

std::string Player::get_player_name() const
{
	return name;
}

Player_State* Player::get_player_state() const
{
	return player_state;
}
        
bool Player::get_is_active() const
{
	return is_active;
}
