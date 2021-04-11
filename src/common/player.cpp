
#include "../../include/common/player.hpp"

Player(Player_id player_id_, bool is_active_) //constructor
{
    player_id = player_id_;
    is_acive = is_active_;
}

Player_id get_player_id() const
{
    return player_id;
}
Player_State* get_player_state() const
{
    return player_state;
}
bool get_is_active() const
{
    return is_active;
}
