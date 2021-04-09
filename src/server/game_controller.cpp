#include "../../include/server/game_controller.hpp"

//constructor, constructs game_state
Game_Controller::Game_Controller()
{
    //create deck
    //draw_pile = deck at initialization
    std::list<ck_Cards::Cards> draw_cards(108);
    for(ck_Cards::Cards card = ck_Cards::Cards::BLUE_0; card != ck_Cards::Cards::WILD_DRAW4_D; ++card)
        draw_cards.push_back(card);

    draw_cards.push_back(ck_Cards::Cards::WILD_DRAW4_D);
    ck_Cards::Draw_Pile* draw_pile = new ck_Cards::Pile(draw_cards);
    //reshuffle draw_pile
    draw_pile->shuffle();
    //retrieve top card
    ck_Cards::Cards top_card = draw_pile->get_top_card();

    while(ck_Cards::Deck::get(top_card).action != ck_Cards::Action::NONE)
    {
        draw_pile->push(top_card);
        top_card = draw_pile->get_top_card();
    }
    std::list<ck_Cards::Cards> discard_cards;
    discard_cards.push_back(top_card);

    ck_Cards::Discard_Pile* discard_pile = new ck_Cards::Pile(discard_cards);
    game_state_ = new game_state(draw_pile, discard_pile);
}


