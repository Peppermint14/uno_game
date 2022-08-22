// Copied from Lama example Project

#include "../../include/common/cards.hpp"


ck_Cards::Deck* ck_Cards::Deck::instance = new ck_Cards::Deck([]{
    std::unordered_map<Cards, std::unique_ptr<Card>> out;
    //insert like this...
    out[Cards::BLUE_0] = std::make_unique<Card>(Cards::BLUE_0, Color::BLUE, Value::ZERO, Action::NONE);
    out[Cards::BLUE_1_A] = std::make_unique<Card>(Cards::BLUE_1_A, Color::BLUE, Value::ONE, Action::NONE);
    out[Cards::BLUE_2_A] = std::make_unique<Card>(Cards::BLUE_2_A, Color::BLUE, Value::TWO, Action::NONE);
    out[Cards::BLUE_3_A] = std::make_unique<Card>(Cards::BLUE_3_A, Color::BLUE, Value::THREE, Action::NONE);
    out[Cards::BLUE_4_A] = std::make_unique<Card>(Cards::BLUE_4_A, Color::BLUE, Value::FOUR, Action::NONE);
    out[Cards::BLUE_5_A] = std::make_unique<Card>(Cards::BLUE_5_A, Color::BLUE, Value::FIVE, Action::NONE);
    out[Cards::BLUE_6_A] = std::make_unique<Card>(Cards::BLUE_6_A, Color::BLUE, Value::SIX, Action::NONE);
    out[Cards::BLUE_7_A] = std::make_unique<Card>(Cards::BLUE_7_A, Color::BLUE, Value::SEVEN, Action::NONE);
    out[Cards::BLUE_8_A] = std::make_unique<Card>(Cards::BLUE_8_A, Color::BLUE, Value::EIGHT, Action::NONE);
    out[Cards::BLUE_9_A] = std::make_unique<Card>(Cards::BLUE_9_A, Color::BLUE, Value::NINE, Action::NONE);
    out[Cards::BLUE_1_B] = std::make_unique<Card>(Cards::BLUE_1_B, Color::BLUE, Value::ONE, Action::NONE);
    out[Cards::BLUE_2_B] = std::make_unique<Card>(Cards::BLUE_2_B, Color::BLUE, Value::TWO, Action::NONE);
    out[Cards::BLUE_3_B] = std::make_unique<Card>(Cards::BLUE_3_B, Color::BLUE, Value::THREE, Action::NONE);
    out[Cards::BLUE_4_B] = std::make_unique<Card>(Cards::BLUE_4_B, Color::BLUE, Value::FOUR, Action::NONE);
    out[Cards::BLUE_5_B] = std::make_unique<Card>(Cards::BLUE_5_B, Color::BLUE, Value::FIVE, Action::NONE);
    out[Cards::BLUE_6_B] = std::make_unique<Card>(Cards::BLUE_6_B, Color::BLUE, Value::SIX, Action::NONE);
    out[Cards::BLUE_7_B] = std::make_unique<Card>(Cards::BLUE_7_B, Color::BLUE, Value::SEVEN, Action::NONE);
    out[Cards::BLUE_8_B] = std::make_unique<Card>(Cards::BLUE_8_B, Color::BLUE, Value::EIGHT, Action::NONE);
    out[Cards::BLUE_9_B] = std::make_unique<Card>(Cards::BLUE_9_B, Color::BLUE, Value::NINE, Action::NONE);
    out[Cards::YELLOW_0] = std::make_unique<Card>(Cards::YELLOW_0, Color::YELLOW, Value::ZERO, Action::NONE);
    out[Cards::YELLOW_1_A] = std::make_unique<Card>(Cards::YELLOW_1_A, Color::YELLOW, Value::ONE, Action::NONE);
    out[Cards::YELLOW_2_A] = std::make_unique<Card>(Cards::YELLOW_2_A, Color::YELLOW, Value::TWO, Action::NONE);
    out[Cards::YELLOW_3_A] = std::make_unique<Card>(Cards::YELLOW_3_A, Color::YELLOW, Value::THREE, Action::NONE);
    out[Cards::YELLOW_4_A] = std::make_unique<Card>(Cards::YELLOW_4_A, Color::YELLOW, Value::FOUR, Action::NONE);
    out[Cards::YELLOW_5_A] = std::make_unique<Card>(Cards::YELLOW_5_A, Color::YELLOW, Value::FIVE, Action::NONE);
    out[Cards::YELLOW_6_A] = std::make_unique<Card>(Cards::YELLOW_6_A, Color::YELLOW, Value::SIX, Action::NONE);
    out[Cards::YELLOW_7_A] = std::make_unique<Card>(Cards::YELLOW_7_A, Color::YELLOW, Value::SEVEN, Action::NONE);
    out[Cards::YELLOW_8_A] = std::make_unique<Card>(Cards::YELLOW_8_A, Color::YELLOW, Value::EIGHT, Action::NONE);
    out[Cards::YELLOW_9_A] = std::make_unique<Card>(Cards::YELLOW_9_A, Color::YELLOW, Value::NINE, Action::NONE);
    out[Cards::YELLOW_1_B] = std::make_unique<Card>(Cards::YELLOW_1_B, Color::YELLOW, Value::ONE, Action::NONE);
    out[Cards::YELLOW_2_B] = std::make_unique<Card>(Cards::YELLOW_2_B, Color::YELLOW, Value::TWO, Action::NONE);
    out[Cards::YELLOW_3_B] = std::make_unique<Card>(Cards::YELLOW_3_B, Color::YELLOW, Value::THREE, Action::NONE);
    out[Cards::YELLOW_4_B] = std::make_unique<Card>(Cards::YELLOW_4_B, Color::YELLOW, Value::FOUR, Action::NONE);
    out[Cards::YELLOW_5_B] = std::make_unique<Card>(Cards::YELLOW_5_B, Color::YELLOW, Value::FIVE, Action::NONE);
    out[Cards::YELLOW_6_B] = std::make_unique<Card>(Cards::YELLOW_6_B, Color::YELLOW, Value::SIX, Action::NONE);
    out[Cards::YELLOW_7_B] = std::make_unique<Card>(Cards::YELLOW_7_B, Color::YELLOW, Value::SEVEN, Action::NONE);
    out[Cards::YELLOW_8_B] = std::make_unique<Card>(Cards::YELLOW_8_B, Color::YELLOW, Value::EIGHT, Action::NONE);
    out[Cards::YELLOW_9_B] = std::make_unique<Card>(Cards::YELLOW_9_B, Color::YELLOW, Value::NINE, Action::NONE);
    out[Cards::GREEN_0] = std::make_unique<Card>(Cards::GREEN_0, Color::GREEN, Value::ZERO, Action::NONE);
    out[Cards::GREEN_1_A] = std::make_unique<Card>(Cards::GREEN_1_A, Color::GREEN, Value::ONE, Action::NONE);
    out[Cards::GREEN_2_A] = std::make_unique<Card>(Cards::GREEN_2_A, Color::GREEN, Value::TWO, Action::NONE);
    out[Cards::GREEN_3_A] = std::make_unique<Card>(Cards::GREEN_3_A, Color::GREEN, Value::THREE, Action::NONE);
    out[Cards::GREEN_4_A] = std::make_unique<Card>(Cards::GREEN_4_A, Color::GREEN, Value::FOUR, Action::NONE);
    out[Cards::GREEN_5_A] = std::make_unique<Card>(Cards::GREEN_5_A, Color::GREEN, Value::FIVE, Action::NONE);
    out[Cards::GREEN_6_A] = std::make_unique<Card>(Cards::GREEN_6_A, Color::GREEN, Value::SIX, Action::NONE);
    out[Cards::GREEN_7_A] = std::make_unique<Card>(Cards::GREEN_7_A, Color::GREEN, Value::SEVEN, Action::NONE);
    out[Cards::GREEN_8_A] = std::make_unique<Card>(Cards::GREEN_8_A, Color::GREEN, Value::EIGHT, Action::NONE);
    out[Cards::GREEN_9_A] = std::make_unique<Card>(Cards::GREEN_9_A, Color::GREEN, Value::NINE, Action::NONE);
    out[Cards::GREEN_1_B] = std::make_unique<Card>(Cards::GREEN_1_B, Color::GREEN, Value::ONE, Action::NONE);
    out[Cards::GREEN_2_B] = std::make_unique<Card>(Cards::GREEN_2_B, Color::GREEN, Value::TWO, Action::NONE);
    out[Cards::GREEN_3_B] = std::make_unique<Card>(Cards::GREEN_3_B, Color::GREEN, Value::THREE, Action::NONE);
    out[Cards::GREEN_4_B] = std::make_unique<Card>(Cards::GREEN_4_B, Color::GREEN, Value::FOUR, Action::NONE);
    out[Cards::GREEN_5_B] = std::make_unique<Card>(Cards::GREEN_5_B, Color::GREEN, Value::FIVE, Action::NONE);
    out[Cards::GREEN_6_B] = std::make_unique<Card>(Cards::GREEN_6_B, Color::GREEN, Value::SIX, Action::NONE);
    out[Cards::GREEN_7_B] = std::make_unique<Card>(Cards::GREEN_7_B, Color::GREEN, Value::SEVEN, Action::NONE);
    out[Cards::GREEN_8_B] = std::make_unique<Card>(Cards::GREEN_8_B, Color::GREEN, Value::EIGHT, Action::NONE);
    out[Cards::GREEN_9_B] = std::make_unique<Card>(Cards::GREEN_9_B, Color::GREEN, Value::NINE, Action::NONE);
    out[Cards::RED_0] = std::make_unique<Card>(Cards::RED_0, Color::RED, Value::ZERO, Action::NONE);
    out[Cards::RED_1_A] = std::make_unique<Card>(Cards::RED_1_A, Color::RED, Value::ONE, Action::NONE);
    out[Cards::RED_2_A] = std::make_unique<Card>(Cards::RED_2_A, Color::RED, Value::TWO, Action::NONE);
    out[Cards::RED_3_A] = std::make_unique<Card>(Cards::RED_3_A, Color::RED, Value::THREE, Action::NONE);
    out[Cards::RED_4_A] = std::make_unique<Card>(Cards::RED_4_A, Color::RED, Value::FOUR, Action::NONE);
    out[Cards::RED_5_A] = std::make_unique<Card>(Cards::RED_5_A, Color::RED, Value::FIVE, Action::NONE);
    out[Cards::RED_6_A] = std::make_unique<Card>(Cards::RED_6_A, Color::RED, Value::SIX, Action::NONE);
    out[Cards::RED_7_A] = std::make_unique<Card>(Cards::RED_7_A, Color::RED, Value::SEVEN, Action::NONE);
    out[Cards::RED_8_A] = std::make_unique<Card>(Cards::RED_8_A, Color::RED, Value::EIGHT, Action::NONE);
    out[Cards::RED_9_A] = std::make_unique<Card>(Cards::RED_9_A, Color::RED, Value::NINE, Action::NONE);
    out[Cards::RED_1_B] = std::make_unique<Card>(Cards::RED_1_B, Color::RED, Value::ONE, Action::NONE);
    out[Cards::RED_2_B] = std::make_unique<Card>(Cards::RED_2_B, Color::RED, Value::TWO, Action::NONE);
    out[Cards::RED_3_B] = std::make_unique<Card>(Cards::RED_3_B, Color::RED, Value::THREE, Action::NONE);
    out[Cards::RED_4_B] = std::make_unique<Card>(Cards::RED_4_B, Color::RED, Value::FOUR, Action::NONE);
    out[Cards::RED_5_B] = std::make_unique<Card>(Cards::RED_5_B, Color::RED, Value::FIVE, Action::NONE);
    out[Cards::RED_6_B] = std::make_unique<Card>(Cards::RED_6_B, Color::RED, Value::SIX, Action::NONE);
    out[Cards::RED_7_B] = std::make_unique<Card>(Cards::RED_7_B, Color::RED, Value::SEVEN, Action::NONE);
    out[Cards::RED_8_B] = std::make_unique<Card>(Cards::RED_8_B, Color::RED, Value::EIGHT, Action::NONE);
    out[Cards::RED_9_B] = std::make_unique<Card>(Cards::RED_9_B, Color::RED, Value::NINE, Action::NONE);
    out[Cards::BLUE_SKIP_A] = std::make_unique<Card>(Cards::BLUE_SKIP_A, Color::BLUE, Value::NONE, Action::SKIP);
    out[Cards::BLUE_SKIP_B] = std::make_unique<Card>(Cards::BLUE_SKIP_B, Color::BLUE, Value::NONE, Action::SKIP);
    out[Cards::YELLOW_SKIP_A] = std::make_unique<Card>(Cards::YELLOW_SKIP_A, Color::YELLOW, Value::NONE, Action::SKIP);
    out[Cards::YELLOW_SKIP_B] = std::make_unique<Card>(Cards::YELLOW_SKIP_B, Color::YELLOW, Value::NONE, Action::SKIP);
    out[Cards::GREEN_SKIP_A] = std::make_unique<Card>(Cards::GREEN_SKIP_A, Color::GREEN, Value::NONE, Action::SKIP);
    out[Cards::GREEN_SKIP_B] = std::make_unique<Card>(Cards::GREEN_SKIP_B, Color::GREEN, Value::NONE, Action::SKIP);
    out[Cards::RED_SKIP_A] = std::make_unique<Card>(Cards::RED_SKIP_A, Color::RED, Value::NONE, Action::SKIP);
    out[Cards::RED_SKIP_B] = std::make_unique<Card>(Cards::RED_SKIP_B, Color::RED, Value::NONE, Action::SKIP);
    out[Cards::BLUE_REVERSE_A] = std::make_unique<Card>(Cards::BLUE_REVERSE_A, Color::BLUE, Value::NONE, Action::REVERSE);
    out[Cards::BLUE_REVERSE_B] = std::make_unique<Card>(Cards::BLUE_REVERSE_B, Color::BLUE, Value::NONE, Action::REVERSE);
    out[Cards::YELLOW_REVERSE_A] = std::make_unique<Card>(Cards::YELLOW_REVERSE_A, Color::YELLOW, Value::NONE, Action::REVERSE);
    out[Cards::YELLOW_REVERSE_B] = std::make_unique<Card>(Cards::YELLOW_REVERSE_B, Color::YELLOW, Value::NONE, Action::REVERSE);
    out[Cards::GREEN_REVERSE_A] = std::make_unique<Card>(Cards::GREEN_REVERSE_A, Color::GREEN, Value::NONE, Action::REVERSE);
    out[Cards::GREEN_REVERSE_B] = std::make_unique<Card>(Cards::GREEN_REVERSE_B, Color::GREEN, Value::NONE, Action::REVERSE);
    out[Cards::RED_REVERSE_A] = std::make_unique<Card>(Cards::RED_REVERSE_A, Color::RED, Value::NONE, Action::REVERSE);
    out[Cards::RED_REVERSE_B] = std::make_unique<Card>(Cards::RED_REVERSE_B, Color::RED, Value::NONE, Action::REVERSE);
    out[Cards::BLUE_DRAW2_A] = std::make_unique<Card>(Cards::BLUE_DRAW2_A, Color::BLUE, Value::NONE, Action::DRAW2);
    out[Cards::BLUE_DRAW2_B] = std::make_unique<Card>(Cards::BLUE_DRAW2_B, Color::BLUE, Value::NONE, Action::DRAW2);
    out[Cards::YELLOW_DRAW2_A] = std::make_unique<Card>(Cards::YELLOW_DRAW2_A, Color::YELLOW, Value::NONE, Action::DRAW2);
    out[Cards::YELLOW_DRAW2_B] = std::make_unique<Card>(Cards::YELLOW_DRAW2_B, Color::YELLOW, Value::NONE, Action::DRAW2);
    out[Cards::GREEN_DRAW2_A] = std::make_unique<Card>(Cards::GREEN_DRAW2_A, Color::GREEN, Value::NONE, Action::DRAW2);
    out[Cards::GREEN_DRAW2_B] = std::make_unique<Card>(Cards::GREEN_DRAW2_B, Color::GREEN, Value::NONE, Action::DRAW2);
    out[Cards::RED_DRAW2_A] = std::make_unique<Card>(Cards::RED_DRAW2_A, Color::RED, Value::NONE, Action::DRAW2);
    out[Cards::RED_DRAW2_B] = std::make_unique<Card>(Cards::RED_DRAW2_B, Color::RED, Value::NONE, Action::DRAW2);
    out[Cards::WILD_A] = std::make_unique<Card>(Cards::WILD_A, Color::NONE, Value::NONE, Action::WILD);
    out[Cards::WILD_B] = std::make_unique<Card>(Cards::WILD_B, Color::NONE, Value::NONE, Action::WILD);
    out[Cards::WILD_C] = std::make_unique<Card>(Cards::WILD_C, Color::NONE, Value::NONE, Action::WILD);
    out[Cards::WILD_D] = std::make_unique<Card>(Cards::WILD_D, Color::NONE, Value::NONE, Action::WILD);
    out[Cards::WILD_DRAW4_A] = std::make_unique<Card>(Cards::WILD_DRAW4_A, Color::NONE, Value::NONE, Action::WILD_DRAW4);
    out[Cards::WILD_DRAW4_B] = std::make_unique<Card>(Cards::WILD_DRAW4_B, Color::NONE, Value::NONE, Action::WILD_DRAW4);
    out[Cards::WILD_DRAW4_C] = std::make_unique<Card>(Cards::WILD_DRAW4_C, Color::NONE, Value::NONE, Action::WILD_DRAW4);
    out[Cards::WILD_DRAW4_D] = std::make_unique<Card>(Cards::WILD_DRAW4_D, Color::NONE, Value::NONE, Action::WILD_DRAW4);

    return out;
});

//to iterate over enum
ck_Cards::Cards& ck_Cards::operator++ (ck_Cards::Cards& it)
{
    if (it == ck_Cards::Cards::WILD_DRAW4_D) {
        throw std::out_of_range("for Cards& operator ++ (Cards&)");
    }
    it = ck_Cards::Cards(static_cast<std::underlying_type<ck_Cards::Cards>::type>(it) + 1);
    return it;

}

std::string ck_Cards::get_color_as_string(const ck_Cards::Color& color)
{
    switch(color)
    {
        case Color::BLUE:
          return "blue";
        case Color::YELLOW:
            return "yellow";
        case Color::RED:
            return "red";
        case Color::GREEN:
            return "green";
        case Color::NONE:
            return "";
        default:
            return "";
    }
}
std::string ck_Cards::Card::get_action_as_string() const
{
    switch(action)
    {
        case Action::SKIP:
            return "skip";
        case Action::REVERSE:
            return "reverse";
        case Action::DRAW2:
            return "draw two";
        case Action::WILD_DRAW4:
            return "wild draw four";
        case Action::WILD:
            return "wild";
        case Action::NONE:
            return "";
        default:
            return "";
    }
}
std::string ck_Cards::Card::get_value_as_string() const
{
    if(value == Value::NONE)
        return "";
    else
        return "";

}

const ck_Cards::Card& ck_Cards::Deck::get(ck_Cards::Cards _card) noexcept {
    assert(instance->cards.count(_card) == 1);
    return *instance->cards.at(_card);
}

const std::vector<std::reference_wrapper<ck_Cards::Card>> ck_Cards::Deck::getByColor(ck_Cards::Color _color) noexcept {
    std::vector<std::reference_wrapper<ck_Cards::Card>> out;
    for(auto it = instance->cards.begin(); it != instance->cards.end(); ++it)
        if(it->second->color == _color)
            out.push_back(std::ref(*it->second));
    return out;
}



//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//PILE

ck_Cards::Pile::Pile(std::list<ck_Cards::Cards> cards_)
{
	cards = cards_;
}

ck_Cards::Pile::Pile() {};


const ck_Cards::Cards ck_Cards::Pile::get_top_card()
{
    if(empty()) throw new ckException("Error: Pile is empty");
    ck_Cards::Cards top_card = cards.back();
    cards.pop_back();
    return top_card;
}

const ck_Cards::Cards ck_Cards::Pile::back()
{
	if(empty()) throw new ckException("Error: Pile is empty");
	return cards.back();
}


void ck_Cards::Pile::push_front(ck_Cards::Cards _card)  {
	cards.push_front(_card);
}


void ck_Cards::Pile::push(Cards _card) noexcept {
    cards.push_back(_card);
}

void ck_Cards::Pile::put_at_end(Cards _card) noexcept {
    cards.push_front(_card);
}


void ck_Cards::Pile::push(const std::list<Cards> _cards) noexcept {
    for(const auto& c : _cards)
        cards.push_back(c);
}

void ck_Cards::Pile::remove(const ck_Cards::Cards card)
{
    cards.remove(card);
}

void ck_Cards::Pile::shuffle() noexcept {
    if(empty()) return;
    std::mt19937_64 gen;
    gen.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::vector<ck_Cards::Cards> tmp(cards.begin(), cards.end());
    std::shuffle(tmp.begin(), tmp.end(), gen);
    cards.clear();
    std::copy(tmp.begin(), tmp.end(), std::front_inserter(cards));
}

size_t ck_Cards::Pile::size() const noexcept{
    return cards.size();
}

bool ck_Cards::Pile::empty() const noexcept{
    return cards.empty();
}

void ck_Cards::Pile::clear() noexcept{
    cards.clear();
}

const std::list<ck_Cards::Cards> ck_Cards::Pile::get_cards() const
{
    return cards;
}
