
#include "../../include/client/player_state.hpp"

// TODO: THIS IS CURRENTLY A TESTING CONSTRUCTOR
//default constructor
Player_State::Player_State()
{
     std::list<ck_Cards::Cards> c = {ck_Cards::Cards::BLUE_0, ck_Cards::Cards::BLUE_1_A, ck_Cards::Cards::BLUE_2_A, ck_Cards::Cards::BLUE_3_A};
     // This was previously a 
     this->hand = new ck_Cards::Hand(c);
     this->number_of_cards = c.size();
     this->players_turn = 1;
     this->play_direction = 1;
     this->current_Player = Player_id::PLAYER_1;
     this->player_won = 0;
     this->player_waiting = 0;
     this->all_Player_Names.resize(4);
     this->all_Player_Names[0] = "test1";
     this->all_Player_Names[1] = "test2";
     this->all_Player_Names[2] = "test3";
     this->all_Player_Names[3] = "test4";
     
}
Player_State::~Player_State(){
     delete hand;
     hand = nullptr;
     number_of_cards = -1;

}

void Player_State::set_players_turn(bool p_turn){
	players_turn = p_turn;
}
void Player_State::set_hand(ck_Cards::Hand* hand_)
 {
     hand = hand_;
     size_t number_of_cards = hand->size();
     set_number_of_cards(number_of_cards);
 }

void Player_State::set_number_of_cards(size_t number_of_cards_)
{
     number_of_cards = number_of_cards_;
}
size_t Player_State::get_number_of_cards()
{
	return number_of_cards;
}
// void Player_State::update_hand(const std::vector<ck_Cards::Cards cards)
// {
//     hand->push(cards);
//     size_t number_of_cards = hand->cards.size();
//     set_number_of_cards(number_of_cards);
// }
//
ck_Cards::Hand* Player_State::get_hand() const
{
     return hand;
}

int Player_State::get_nof_cards() const{
     return number_of_cards;
}

bool Player_State::get_players_turn() const {
     return players_turn;
}

// TODO: Handle player names
void Player_State::set_all_player_names(){

}


void Player_State::change_play_direction(){
     play_direction = !play_direction;
}
Player_id Player_State::get_current_player() const {
     return current_Player;
}
bool Player_State::has_player_won() const {
     return player_won;
}
bool Player_State::is_waiting() const {
     return player_waiting;
}
std::string Player_State::get_player_name() const {
     return all_Player_Names[uint32_t(current_Player)];
}
