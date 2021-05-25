#include <gtest/gtest.h>

#include "../../include/server/game_controller.hpp"
#include "../../include/common/common.hpp"
#include <vector>


using namespace ck_Cards;
class ParametricValidCard : public ::testing::TestWithParam<std::pair<ck_Cards::Cards, bool> > {
	
protected:
	virtual void SetUp()
	{
		game_controller.get_game_state()->get_discard_pile().push(ck_Cards::Cards::RED_5_A);
		//std::list<ck_Cards::Cards> cards = {Cards::BLUE_1_A, Cards::RED_4_A, Cards::GREEN_0};
		//cards.push_back(Cards::RED_0);
		//discard_pile.push( cards);
	}
	 
	Game_Controller game_controller;
	Discard_Pile discard_pile;
	
	
};

const std::vector<std::pair<ck_Cards::Cards, bool> > played_cards = {
	{ck_Cards::Cards::GREEN_2_A,0},
	{ck_Cards::Cards::GREEN_5_A,1},
	{ck_Cards::Cards::RED_4_A,1},
	{ck_Cards::Cards::WILD_A,1},
	{ck_Cards::Cards::RED_DRAW2_A,1},
	{ck_Cards::Cards::BLUE_DRAW2_A,0},
	{ck_Cards::Cards::RED_REVERSE_A,1},
	{ck_Cards::Cards::BLUE_REVERSE_A,0},
	{ck_Cards::Cards::RED_SKIP_A,1},
	{ck_Cards::Cards::BLUE_SKIP_A,0} };



TEST_P(ParametricValidCard, Validmove)
{
    std::pair<ck_Cards::Cards, bool> cards = GetParam();
    bool actual_output = game_controller.valid_move(cards.first);
    bool expected_output = cards.second;
    EXPECT_EQ(actual_output, expected_output);
}

INSTANTIATE_TEST_SUITE_P(Validmove, ParametricValidCard, testing::ValuesIn(played_cards));


class Game_State_Test : public ::testing::Test {

protected:
    virtual void SetUp() 
    {   
      Player* player0 = new Player(Player_id::PLAYER_1, "player_1");
      Player* player1 = new Player(Player_id::PLAYER_2, "player_2");
      Player* player2 = new Player(Player_id::PLAYER_3, "player_3");
    
      //assumed to be correct
      game_controller.get_game_state()->add_Players(player0);
      game_controller.get_game_state()->add_Players(player1);
      game_controller.get_game_state()->add_Players(player2);	
        
      game_controller.get_game_state()->get_player(Player_id::PLAYER_1)->get_hand().push({Cards::RED_DRAW2_A, Cards::BLUE_SKIP_A, Cards::GREEN_2_A});
      
      game_controller.get_game_state()->get_player(Player_id::PLAYER_2)->get_hand().push({Cards::RED_4_B, Cards::RED_REVERSE_B, Cards::RED_SKIP_B});
      
      game_controller.get_game_state()->get_player(Player_id::PLAYER_3)->get_hand().push({Cards::RED_4_A, Cards::RED_REVERSE_A, Cards::RED_SKIP_A});      
      
      game_controller.get_game_state()->set_current_player(Player_id::PLAYER_1);

      //std::list<ck_Cards::Cards> draw_pile_list =
      std::list<ck_Cards::Cards> discard_pile_list = {
              ck_Cards::Cards::GREEN_1_A,ck_Cards::Cards::BLUE_SKIP_A, ck_Cards::Cards::RED_0};
      ck_Cards::Draw_Pile draw_pile; //empty draw_pile
      ck_Cards::Discard_Pile discard_pile;
      discard_pile.push(discard_pile_list);
      discard_pile.push(ck_Cards::Cards::BLUE_0);
    }

    /* Any object and subroutine declared here can be accessed in the tests */
    Game_Controller game_controller;

};

// testing function get_player_id()
TEST_F(Game_State_Test, PlayerId)
{
  Player_id player2_Id = game_controller.get_game_state()->get_player(Player_id::PLAYER_3)->get_player_id();
  Player_id expected_player2_Id = Player_id::PLAYER_3;
  EXPECT_EQ(expected_player2_Id, player2_Id);
  
}

// testing function get_current_player()
TEST_F(Game_State_Test, CurrentPlayer)
{
  Player_id current_player = game_controller.get_game_state()->get_current_player();
  Player_id expected_current_player = Player_id::PLAYER_1;
  EXPECT_EQ(expected_current_player, current_player);
  
}

// testing iteration to the next player
TEST_F(Game_State_Test, SkipWinningPlayer)
{
    //uses has_won maybe test first
    game_controller.get_game_state()->get_player(Player_id::PLAYER_2)->set_has_won(true);
    Player_id next_player = game_controller.get_next_player(Player_id::PLAYER_1);
    Player_id expected_next_player = Player_id::PLAYER_3;
    EXPECT_EQ(expected_next_player, next_player);
}

// testing iteration to the next player loop back to PLAYER_1
TEST_F(Game_State_Test, GetNextPlayerLoop)
{
  Player_id next_player = game_controller.get_next_player(Player_id::PLAYER_3);
  Player_id expected_next_player = Player_id::PLAYER_1;
  EXPECT_EQ(expected_next_player, next_player);
}

// testing action SKIP
TEST_F(Game_State_Test, SwitchPlayer)
{
  game_controller.switch_player(Player_id::PLAYER_1);
  Player_id next_player = game_controller.get_game_state()->get_current_player();
  Player_id expected_next_player = Player_id::PLAYER_2;
  EXPECT_EQ(expected_next_player, next_player);
}

// testing action REVERSE
TEST_F(Game_State_Test, Reverse)
{
  //reverse order of vec players
  std::reverse(game_controller.get_game_state()->get_players().begin(), game_controller.get_game_state()->get_players().end());
  
  //change current_player
  Player_id player_id = game_controller.get_game_state()->get_current_player();
  game_controller.switch_player(player_id);

  Player_id next_player = game_controller.get_game_state()->get_current_player();
  Player_id expected_next_player = Player_id::PLAYER_3; // start in SetUp() at 1 and reverse should be 3
  EXPECT_EQ(expected_next_player, next_player);
}


TEST_F(Game_State_Test, Reshuffle)
{
    size_t expected_size_draw_pile = game_controller.get_game_state()->get_discard_pile().size()-2;
    game_controller.draw_card(Player_id::PLAYER_1);
    size_t actual_size_draw_pile = game_controller.get_game_state()->get_draw_pile().size();

    EXPECT_EQ(expected_size_draw_pile, actual_size_draw_pile);
}
// testing deck reshuffle (scenario SCN-1 from SRS)


// testing only two Players are in the game and one leaves (scenario SCN-2 from SRS)


// testing one player exits but more than one player are still in the game (scenario SCN-3 from SRS)


// testing player wins game in a game in which more than 2 players are participating (scenario SCN-4 from SRS)


// testing timeout : player doesn’t play in a given time slot, a card will automatically be handed out to the player
//          and the player misses this turn. (FREQ-17 from SRS)


// testing The system should not allow any additional user to join a game once the game has started. (FREQ-13)

//test if card has been played and is now top_card of discard_pile
TEST_F(Game_State_Test, Update_discard_pile)
{
  game_controller.get_game_state()->get_discard_pile().push(Cards::BLUE_5_A);

  nlohmann::json msg_json;
  msg_json["type"]= Request_Type::PLAY_REQUEST;
  msg_json["card"]=Cards::BLUE_SKIP_A;
  msg_json["id"]=1;

  game_controller.eval_request(Player_id::PLAYER_1, msg_json.dump());
  
  const Cards topCard = game_controller.get_game_state()->get_discard_pile().get_top_card();
  const Cards expected_topCard = Cards::BLUE_SKIP_A;
  EXPECT_EQ(expected_topCard, topCard);
}

//check if draw_2 cards adds cards to next player
TEST_F(Game_State_Test, Draw2)
{
  game_controller.get_game_state()->get_discard_pile().push(Cards::RED_5_B);
  
  // player1 plays a red draw2 card on top of the red discard pile
  nlohmann::json msg_json;
  msg_json["type"]= Request_Type::PLAY_REQUEST;
  msg_json["id"]=1;
  msg_json["card"]=Cards::RED_DRAW2_A;
  
  game_controller.eval_request(Player_id::PLAYER_1, msg_json.dump());
  
  // player2 will get 2 extra cards, going from 3 to 5
  const size_t nbCards = game_controller.get_game_state()->get_player(Player_id::PLAYER_2)->number_of_cards();
  const size_t expected_nbCards = 5;
  EXPECT_EQ(expected_nbCards, nbCards);
}

//check if color was updated
TEST_F(Game_State_Test, UpdateColor)
{
  game_controller.get_game_state()->get_discard_pile().push(Cards::GREEN_5_B);
  
  // player1 plays a red draw2 card on top of the red discard pile
  nlohmann::json msg_json;
  msg_json["type"]= Request_Type::PLAY_REQUEST;
  msg_json["id"]=1;
  msg_json["card"]=Cards::GREEN_2_A;
  
  game_controller.eval_request(Player_id::PLAYER_1, msg_json.dump());
  
  Color color = game_controller.get_game_state()->get_color_to_be_matched();
  Color expected_color = Color::GREEN;
  EXPECT_EQ(expected_color, color);
}


//check if card was removed after hand was played
/*
TEST_F(Game_State_Test, Update_hand)
{
  
  nlohmann::json msg_json;
  msg_json["type"]= Request_Type::PLAY_REQUEST;
  msg_json["unique_player_id"]=0;
  msg_json["card"]=Cards::RED_DRAW2_A;
  
  game_controller.eval_request(Player_id::PLAYER_1, msg_json.dump());
  
  const Cards topCard = game_controller.get_game_state()->get_players()[0].get_hand();
  const Cards expected_topCard = Cards::BLUE_SKIP_A;
  EXPECT_EQ(expected_topCard, topCard);
}
*/

//check reshuffling of draw_pile


//check if hand can be sended


int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


// ----------some other test ideas------------------
// testing deck reshuffle (scenario SCN-1 from SRS)

// testing only two Players are in the game and one leaves (scenario SCN-2 from SRS)

// testing one player exits but more than one player are still in the game (scenario SCN-3 from SRS)

// testing player wins game in a game in which more than 2 players are participating (scenario SCN-4 from SRS)

// testing timeout : player doesn’t play in a given time slot, a card will automatically be handed out to the player
//          and the player misses this turn. (FREQ-17 from SRS)

// testing The system should not allow any additional user to join a game once the game has started. (FREQ-13)

// testing The system should allow a user to exit the game at any given moment. (FREQ-9)

