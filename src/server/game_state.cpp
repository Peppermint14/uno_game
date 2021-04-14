#include "../../include/server/game_state.hpp"

//default constructor
Game_State::Game_State(ck_Cards::Draw_Pile* draw_pile_, ck_Cards::Discard_Pile* discard_pile_)
{
    discard_pile = discard_pile_;
    draw_pile = draw_pile_;
    color_to_be_matched = ck_Cards::Deck::get(discard_pile->front()).color;
}

void Game_State::add_Players(Player* player)
{
    //maybe take player id as argument and generate player
    players.push_back(player);
}

void Game_State::set_current_player(Player_id id)
{
	current_player = id;

}

void Game_State::set_color_to_be_matched(ck_Cards::Color color)
{
	color_to_be_matched = color;
}

ck_Cards::Discard_Pile* Game_State::get_discard_pile() const
{
    return discard_pile;
}

Player_id Game_State::get_current_player() const
{
    return current_player;
}

ck_Cards::Color Game_State::get_color_to_be_matched() const
{
    return color_to_be_matched;
}



