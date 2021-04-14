
#include "../../include/common/player.hpp"

Player::Player(Player_id player_id_, bool is_active_) //constructor
{
    player_id = player_id_;
    is_active = is_active_;
}

Player_id Player::get_player_id() const
{
    return player_id;
}
Player_State* Player::get_player_state() const
{
    return player_state;
}
bool Player::get_is_active() const
{
    return is_active;
}
