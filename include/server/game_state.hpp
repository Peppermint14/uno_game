#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../common/common.hpp" //for player_id
#include "../common/cards.hpp"
#include "../common/player.hpp"
#include <list>

class game_state
{
public:
	game_state(ck_Cards::Draw_Pile* /*draw_pile_*/, ck_Cards::Discard_Pile* /*discard_pile*/); //constructor
	void set_current_player(Player_id);
	void set_color_to_be_matched(ck_Cards::Color);
	void add_Players(Player* /*player_*/);
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
