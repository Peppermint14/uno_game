// Copied from Lama example Project

#include "../../include/common/cards.hpp"

ck_Cards::Deck* ck_Cards::Deck::instance = new ck_Cards::Deck([]{
    std::unordered_map<Cards, std::unique_ptr<Card>> out;
    //insert like this...
    out[Cards::TEST_BLUE_4_A] = std::make_unique<Card>(Cards::TEST_BLUE_4_A, Color::BLUE);
    return out;
});

const ck_Cards::Card& ck_Cards::Deck::get(ck_Cards::Cards _card) noexcept {
    assert(instance->cards.count(_card) == 1);
    return *instance->cards.find(_card)->second;
}

const std::vector<std::reference_wrapper<ck_Cards::Card>> ck_Cards::Deck::getByColor(ck_Cards::Color _color) noexcept {
    std::vector<std::reference_wrapper<ck_Cards::Card>> out;
    for(auto it = instance->cards.begin(); it != instance->cards.end(); ++it)
        if(it->second->color == _color)
            out.push_back(std::ref(*it->second));
    return out;
}

ck_Cards::Cards ck_Cards::Pile::top() const {
    if(empty()) throw new ckException("Error: Pile is empty");
    return cards.front();
}

void ck_Cards::Pile::pop() {
    if(empty()) throw new ckException("Error: Pile is already empty");
    cards.erase(cards.begin());
}

void ck_Cards::Pile::push(Cards _card) noexcept {
    cards.push_back(_card);
}

void ck_Cards::Pile::push(const std::vector<Cards> _cards) noexcept {
    for(const auto& c : _cards)
        cards.push_back(c);
}  

void ck_Cards::Pile::shuffle() noexcept {
    if(empty()) return;
    std::mt19937_64 gen;
    gen.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::vector tmp(cards.begin(), cards.end());
    std::shuffle(tmp.begin(), tmp.end(), gen);
    cards.clear();
    std::copy(tmp.begin(), tmp.end(), std::front_inserter(cards));
}

bool ck_Cards::Pile::size() const noexcept{
    return cards.size();
}

bool ck_Cards::Pile::empty() const noexcept{
    return cards.empty();
}

void ck_Cards::Pile::clear() noexcept{
    cards.clear();
}

void ck_Cards::Pile::from_json(const std::string& _json) {
    if(!empty()) throw new ckException("Pile needs to be empty first. call clear()");
    auto vals = nlohmann::json::parse(_json);
    std::copy(vals["cards"].begin(), vals["cards"].end(), std::front_inserter(cards)); 
}

const std::string ck_Cards::Pile::to_json() const noexcept {
    nlohmann::json json(cards);
    return json.dump();
}

bool ck_Cards::Pile::valid(ck_Cards::Cards _card) const noexcept {
    return !(std::find(cards.begin(), cards.end(), _card) == cards.end());
}
