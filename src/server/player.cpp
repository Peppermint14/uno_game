
#include "../../include/server/player.hpp"

//constructor
Player::Player(const Player_id& player_id_, const std::string& player_name_) : player_id(player_id_), player_name(player_name_)
{
    has_won = false;
    players_turn = false;
};

const Player_id& Player::get_player_id() const
{
    return player_id;
}

void Player::set_has_won(bool has_won_)
{
    has_won = has_won_;
}

Player_id Player::get_player_id() const
{
    return player_id;
}

bool Player::get_is_active() const
{
    return is_active;
}

ck_Cards::Hand& Player::get_hand()
{
    return hand;
}


const std::string& Player::get_player_name() const
{
    return player_name;
}

