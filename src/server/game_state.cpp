#include "../../include/server/game_state.hpp"

//default constructor
Game_State::Game_State(ck_Cards::Draw_Pile* draw_pile_, ck_Cards::Discard_Pile* discard_pile_)
{
    discard_pile = discard_pile_;
    draw_pile = draw_pile_; //maybe should be another default value before game has started
    color_to_be_matched = ck_Cards::Deck::get(discard_pile->front()).color; //maybe should be another default value before game was started
    current_player = Player_id::PLAYER_ERROR;
    has_started = false;
}

void Game_State::add_Players(Player* player)
{
    //maybe take player id as argument and generate player
    players.push_back(std::pair<Player_id,Player*>(player->get_player_id(),player));
}

void Game_State::set_current_player(const Player_id& id)
{
	current_player = id;

}

void Game_State::set_color_to_be_matched(const ck_Cards::Color& color)
{
	color_to_be_matched = color;
}

ck_Cards::Discard_Pile* Game_State::get_discard_pile() const
{
    return discard_pile;
}

ck_Cards::Draw_Pile* Game_State::get_draw_pile() const
{
    return draw_pile;
}

std::vector<std::pair<Player_id, Player*> >& Game_State::get_players()
{
    return players;
}

const Player_id& Game_State::get_current_player() const
{
    return current_player;
}

const ck_Cards::Color& Game_State::get_color_to_be_matched() const
{
    return color_to_be_matched;
}

const bool& Game_State::get_has_started() const
{
    return has_started;
}
void Game_State::set_has_started(bool has_started_)
{
   has_started = has_started_;
}

Player* Game_State::get_player(const Player_id& player_id) const
{
    for(auto iter = players.begin(); iter != players.end(); ++iter)
    {
        if(iter->first == player_id)
            return iter->second;
    }
    //TODO: write better error message
    throw new ckException("Error: no player with such player_id");
    return 0;
}

void Game_State::remove_player(const Player_id& player_id)
{
    for(auto iter = players.begin(); iter != players.end(); ++iter)
    {
        if(iter->first == player_id)
            players.erase(iter);
    }
}



