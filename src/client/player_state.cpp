
#include "../../include/client/player_state.hpp"

//default constructor
Player_State::Player_State()
{
    has_won = 0;
    players_turn = 0;
    number_of_cards = 0;
}

void Player_State::set_hand(ck_Cards::Hand* hand_);
{
    hand = *hand_;
    size_t number_of_cards = hand->cards.size();
    set_number_of_cards(number_of_cards);
}

void Player_State::set_number_of_cards(size_t number_of_cards_)
{
    number_of_cards = number_of_cards_;
}

void Player_State::update_hand(const std::vector<ck_Cards::Cards cards)
{
    hand->push(cards);
    size_t number_of_cards = hand->cards.size();
    set_number_of_cards(number_of_cards);
}

ck_Cards::Hand* Player_State::get_hand() const
{
    return hand;
}