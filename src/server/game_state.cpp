
#include "../../include/server/game_state.hpp"


//default constructor
Game_State::Game_State()
{
    //create deck
    //draw_pile = deck at initialization
    std::list<ck_Cards::Cards> draw_cards;//108
    //loop over enum class
    for(ck_Cards::Cards card = ck_Cards::Cards::BLUE_0; card != ck_Cards::Cards::WILD_DRAW4_D; ++card)
        draw_cards.push_back(card);

    draw_cards.push_back(ck_Cards::Cards::WILD_DRAW4_D);
    draw_pile.push(draw_cards);
    //reshuffle draw_pile
    draw_pile.shuffle();
    //retrieve top card
    ck_Cards::Cards top_card = draw_pile.get_top_card();

    while(ck_Cards::Deck::get(top_card).action != ck_Cards::Action::NONE)
    {
        draw_pile.put_at_end(top_card);
        top_card = draw_pile.get_top_card();
    }

    discard_pile.push(top_card);
    color_to_be_matched = ck_Cards::Deck::get(discard_pile.back()).color; //maybe should be another default value before game was started
    current_player = Player_id::NONE;
    has_started = false;
}

Game_State::~Game_State()
{
    for(auto& player : players)
    {
        delete player.second;
    }
}

void Game_State::set_draw_pile(const ck_Cards::Draw_Pile& draw_pile_)
{
    draw_pile = draw_pile_;
}

void Game_State::set_discard_pile(const ck_Cards::Discard_Pile& discard_pile_)
{
    discard_pile = discard_pile_;
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

ck_Cards::Discard_Pile& Game_State::get_discard_pile()
{
    return discard_pile;
}

ck_Cards::Draw_Pile& Game_State::get_draw_pile()
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

bool Game_State::check_if_player_exists(const Player_id& player_id) const
{
    for(auto iter = players.begin(); iter != players.end(); ++iter)
    {
        if(iter->first == player_id)
            return true;
    }
    return false;
}

Player* Game_State::get_player(const Player_id& player_id) const
{
    for(auto iter = players.begin(); iter != players.end(); ++iter)
    {
        if(iter->first == player_id)
            return iter->second;
    }
    //TODO: write better error message
    throw ckException("Error: no player with such player_id");
    return 0;
}

void Game_State::remove_player(const Player_id& player_id)
{
    auto find_player = [this](Player_id player_id) {
        for(auto iter = players.begin(); iter != players.end(); ++iter)
            if(iter->first == player_id)
            {
                return iter;
            }
        return players.end();
    };
    auto iterator = find_player(player_id);
    delete iterator->second;
    players.erase(iterator);
}

bool Game_State::have_all_won() const
{
    size_t number_of_winners = 0;
    for(const auto& elem : players )
    {
        number_of_winners += elem.second->get_has_won();
    }
    if(number_of_winners == players.size()-1)
        return true;
    else
        return false;
}



