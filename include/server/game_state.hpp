#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../common/common.hpp" //for player_id
#include "../common/cards.hpp"
#include "player.hpp"
#include <list>

class Game_State
{
public:
	Game_State(ck_Cards::Draw_Pile* /*draw_pile_*/, ck_Cards::Discard_Pile* /*discard_pile_*/); //constructor
	void set_current_player(Player_id& /*id*/);
	void set_color_to_be_matched(ck_Cards::Color& /*color*/);
	void add_Players(Player* /*player_*/);
	ck_Cards::Discard_Pile* get_discard_pile() const;
	ck_Cards::Draw_Pile* get_draw_pile() const;
	const std::vector<Player*>& get_players() const;
	const Player_id& get_current_player() const;
	const ck_Cards::Color& get_color_to_be_matched() const;
	//string to_json(), serialize Game State
 	//void from_json(string), deserialize Game State
private:
	ck_Cards::Draw_Pile* draw_pile;
	ck_Cards::Discard_Pile* discard_pile;
	std::vector<Player*> players;
	Player_id current_player;
	ck_Cards::Color color_to_be_matched;
};

#endif /* GAME_STATE_HPP */
