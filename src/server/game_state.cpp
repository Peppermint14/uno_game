#include "../../include/server/game_state.hpp"

void set_current_player(Player_id);
	void set_color_to_be_matched(ck_Cards::Color);

void game_state::set_current_player(Player_id id)
{
	current_player = id;

}

void game_state::set_color_to_be_matched(ck_Cards::Color color)
{
	color_to_be_matched = color;
}



