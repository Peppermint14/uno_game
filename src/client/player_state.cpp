
#include "../../include/client/player_state.hpp"

// TODO: THIS IS CURRENTLY A TESTING CONSTRUCTOR
//default constructor
Player_State::Player_State(){
     this->top_discard = ck_Cards::Cards(0); // Would be nullptr if discard empty
     this->discard_empty = 0; //TODO: Check if necessary

     std::list<ck_Cards::Cards> c = {ck_Cards::Cards::BLUE_0};
     this->hand = new ck_Cards::Hand(c);
     //this->number_of_cards = c.size();
     this->to_be_matched = ck_Cards::Color::NONE;
     this->players_turn = 0;
     this->play_direction = 1;
     this->current_Player = Player_id::NONE;// Player_id::PLAYER_1;
     this->this_player = Player_id::PLAYER_1;
     this->winner = Player_id::PLAYER_3;
     this->player_won = 0;
     this->player_quit = 0;
     this->waiting_for_start = 1;
     this->uno = 0;
     this->match_colour = 0;

     this->number_of_cards.reserve(4);
     this->number_of_cards.push_back(0);
     this->number_of_cards.push_back(0);
     this->number_of_cards.push_back(0);
     this->number_of_cards.push_back(0);


     this->all_Player_Names.reserve(4);
     // TODO: Initialize with player list received from server
     this->all_Player_Names.push_back("test_name 1");
     this->all_Player_Names.push_back("test_name 2");
     this->all_Player_Names.push_back("test_name 3");
     this->all_Player_Names.push_back("test_name 4");

     this->player_ids.reserve(4);
     this->player_ids.push_back(Player_id::PLAYER_1);
     this->player_ids.push_back(Player_id::PLAYER_2);
     this->player_ids.push_back(Player_id::PLAYER_3);
     this->player_ids.push_back(Player_id::PLAYER_4);
    
//:::::::::::::::::::   
/*	this->top_discard = ck_Cards::Cards(0);
     this->discard_empty = 1; //TODO: Check if necessary

     std::list<ck_Cards::Cards> c = {};
     this->hand = new ck_Cards::Hand(c);
     //this->number_of_cards = c.size();
     this->to_be_matched = ck_Cards::Color::NONE;
     this->players_turn = 0;
     this->play_direction = 1;
     this->current_Player = Player_id::NONE;
     this->this_player = Player_id::NONE;
     this->winner = Player_id::NONE;
     this->player_won = 0;
     this->player_quit = 0;
     this->waiting_for_start = 0;
     this->uno = 0;
     this->match_colour = 0;

     // this->number_of_cards.reserve(4);

     // this->all_Player_Names.reserve(4);

     // this->player_ids.reserve(4);
     */
}

Player_State::Player_State(Player_id id, std::string player_name, size_t nof_players):Player_State(){
     
     size_t id_t = static_cast<size_t>(id);
     assert(id_t <= nof_players && id_t > 0);

     this->this_player = id;
     this->number_of_cards.resize(nof_players);
     this->all_Player_Names.resize(nof_players);
     this->player_ids.resize(nof_players);

     this->all_Player_Names[id_t-1] = player_name;
     this->player_ids[id_t-1] = id;

}

// TODO: THIS IS CURRENTLY A TESTING CONSTRUCTOR remove
Player_State::Player_State(bool test)
{
     this->top_discard = ck_Cards::Cards::RED_5_A; // Would be nullptr if discard empty
     this->discard_empty = 0; //TODO: Check if necessary

     std::list<ck_Cards::Cards> c = {ck_Cards::Cards::BLUE_0, ck_Cards::Cards::BLUE_1_A, ck_Cards::Cards::BLUE_2_A, ck_Cards::Cards::BLUE_3_A};
     this->hand = new ck_Cards::Hand(c);
     //this->number_of_cards = c.size();
     this->to_be_matched = ck_Cards::Color::NONE;
     this->players_turn = 0;
     this->play_direction = 1;
     this->current_Player = Player_id::PLAYER_4;// Player_id::PLAYER_1;
     this->this_player = Player_id::PLAYER_1;
     this->winner = Player_id::PLAYER_3;
     this->player_won = 1;
     this->player_quit = 0;
     this->waiting_for_start = 1;
     this->uno = 0;
     this->match_colour = 0;

     this->number_of_cards.reserve(4);
     this->number_of_cards.push_back(0);
     this->number_of_cards.push_back(0);
     this->number_of_cards.push_back(0);
     this->number_of_cards.push_back(0);


     this->all_Player_Names.reserve(4);
     // TODO: Initialize with player list received from server
     this->all_Player_Names.push_back("test_name 1");
     this->all_Player_Names.push_back("test_name 2");
     this->all_Player_Names.push_back("test_name 3");
     this->all_Player_Names.push_back("test_name 4");

     this->player_ids.reserve(4);
     this->player_ids.push_back(Player_id::PLAYER_1);
     this->player_ids.push_back(Player_id::PLAYER_2);
     this->player_ids.push_back(Player_id::PLAYER_3);
     this->player_ids.push_back(Player_id::PLAYER_4);
     
}

Player_State::~Player_State(){
     delete hand;
     hand = nullptr;
}

void Player_State::set_top_discard(ck_Cards::Cards new_top){
     top_discard = new_top;
     discard_empty = 0;
}

void Player_State::set_players_turn(bool p_turn){
	players_turn = p_turn;
}
void Player_State::set_hand(ck_Cards::Hand* hand_)
 {   
     delete hand;
     hand = hand_;
     size_t nof_cards = hand->size();
     set_number_of_cards(this_player, nof_cards);
 }

void Player_State::set_number_of_cards(Player_id p_id, size_t number_of_cards_)
{
     number_of_cards[uint32_t(p_id)-1] = number_of_cards_;
}
void Player_State::set_current_player(Player_id id){
     current_Player = id;
}
void Player_State::set_winner(Player_id id){
     winner = id;
}

// void Player_State::update_hand(const std::vector<ck_Cards::Cards cards)
// {
//     hand->push(cards);
//     size_t number_of_cards = hand->cards.size();
//     set_number_of_cards(number_of_cards);
// }
//

void Player_State::set_all_player_names(std::vector<std::string> name_vec){
     all_Player_Names = name_vec;
}
void Player_State::set_is_waiting(bool waiting){
     player_waiting = waiting;
}
void Player_State::set_uno(bool u){
     uno = u;
}
void Player_State::set_match_colour(bool b){
     b = match_colour;
}
void Player_State::change_play_direction(){
     play_direction = !play_direction;
}
bool Player_State::get_play_direction() const{
     return play_direction;
}
void Player_State::set_to_be_matched(ck_Cards::Color c){
     to_be_matched = c;
}

ck_Cards::Cards* Player_State::get_top_discard(){
     if(discard_empty)return nullptr;
     return &top_discard;
}

ck_Cards::Hand* Player_State::get_hand() const
{
     return hand;
}
ck_Cards::Color Player_State::get_to_be_matched() const{
     return to_be_matched;
}
size_t Player_State::get_number_of_cards(Player_id p_id) const{
     return number_of_cards[uint32_t(p_id)-1];
}

bool Player_State::get_players_turn() const {
     return players_turn;
}

Player_id Player_State::get_current_player() const {
     return current_Player;
}
Player_id Player_State::get_this_player() const {
     return this_player;
}

Player_id Player_State::get_winner() const {
     return winner;
}
bool Player_State::has_player_won() const {
     return player_won;
}
bool Player_State::is_waiting_for_start() const {
     return waiting_for_start;
}
void Player_State::set_is_waiting_for_start(bool waiting){
	waiting_for_start = waiting;
}

bool Player_State::has_player_quit() const {
     return player_quit;
}
bool Player_State::get_uno() const {
     return uno;
}
bool Player_State::get_match_colour() const {
     return match_colour;
}
std::string Player_State::get_player_name() const { 
     return all_Player_Names[uint32_t(current_Player)-1]; // Since our player ids start with 1 (0 <=> error)
}
std::vector<Player_id>* Player_State::get_id_vec(){
     return &player_ids;
}

std::string Player_State::get_name_of_playerid(Player_id id) const{
	return all_Player_Names[uint32_t(id)-1];
}
void Player_State::set_n_players(int n){
	n_player_in_game = n;	
};

int Player_State::get_n_players(){
	return n_player_in_game;
};
