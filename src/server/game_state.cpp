#include "../../include/server/game_state.hpp"

//default constructor
game_state::game_state(ck_Cards::Draw_Pile* draw_pile_, ck_Cards::Discard_Pile* discard_pile_)
{
    discard_pile = discard_pile_;
    draw_pile = draw_pile_;
    color_to_be_matched = ck_Cards::Deck::get(discard_pile->front()).color;
}

void game_state::add_Players(Player* player)
{
    //maybe take player id as argument and generate player
    players.push_back(player);
}

void game_state::set_current_player(Player_id id)
{
	current_player = id;

}

void game_state::set_color_to_be_matched(ck_Cards::Color color)
{
	color_to_be_matched = color;
}



