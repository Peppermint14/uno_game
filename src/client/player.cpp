#include "../../include/client/player.hpp"
#include "../../include/client/player_state.hpp"


Player::Player(Player_State* playerState)
{
	player_state = playerState;
}

void Player::set_is_active(bool active)
{
	is_active = active; 	
}

Player_id Player::get_player_id() const
{
	return player_id;
}
void Player::set_player_id(Player_id _id){
	player_id = _id;	
}


std::string Player::get_player_name() const{
	return player_name;
}

void Player::set_player_name(std::string Name){
	player_name = Name;
}

Player_State* Player::get_player_state() const
{
	return player_state;
}
        
bool Player::get_is_active() const
{
	return is_active;
}
bool Player::is_waiting()const{
     return _is_waiting;
}

bool Player::has_won()const{
     return _has_won;
}
