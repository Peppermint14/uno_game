#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../common/common.hpp" //for player_id
#include "../common/cards.hpp"
#include "player.hpp"
#include <vector>
#include <algorithm> //for std::reverse

class Game_State
{
public:
	Game_State(ck_Cards::Draw_Pile* /*draw_pile_*/, ck_Cards::Discard_Pile* /*discard_pile_*/); //constructor
	void set_current_player(const Player_id& /*id*/);
	void set_color_to_be_matched(const ck_Cards::Color& /*color*/);
	void add_Players(Player* /*player_*/);
	ck_Cards::Discard_Pile* get_discard_pile() const;
	ck_Cards::Draw_Pile* get_draw_pile() const;
	std::vector<std::pair<Player_id, Player*> >& get_players();
	const Player_id& get_current_player() const;
	const ck_Cards::Color& get_color_to_be_matched() const;
	const bool& get_has_started() const;
	void set_has_started(bool /*has_started_*/);
	//return Player with player_id in vector players
	Player* get_player(Player_id /*player_id*/) const;
	//removes player from vector of players
	void remove_player(Player_id /*player_id*/);
private:
	ck_Cards::Draw_Pile* draw_pile;
	ck_Cards::Discard_Pile* discard_pile;
	std::vector<std::pair<Player_id, Player*> > players;
	Player_id current_player;
	ck_Cards::Color color_to_be_matched;
	bool has_started;
};

#endif /* GAME_STATE_HPP */
