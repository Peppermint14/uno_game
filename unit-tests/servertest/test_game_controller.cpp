#include <gtest/gtest.h>

#include "../../include/server/game_controller.hpp"


using namespace ck_Cards;
class ParametricValidCard : public ::testing::TestWithParam<std::pair<ck_Cards::Cards, bool> > {
	
protected:
	virtual void SetUp()
	{
		game_controller.get_game_state()->get_discard_pile().push(ck_Cards::Cards::RED_5_A);
		std::list<ck_Cards::Cards> cards = {Cards::BLUE_1_A, Cards::RED_4_A, Cards::GREEN_0};
		cards.push_back(Cards::RED_0);
		discard_pile.push( cards);
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


//What is testing for an object????
//Thats our Test Fixture
class Game_StateTest : public ::testing::Test {

//why protected????
protected:
    virtual void SetUp() 
    {   
      Player* player0 = new Player(Player_id::PLAYER_1, "player_1");
      Player* player1 = new Player(Player_id::PLAYER_2, "player_2");
      Player* player2 = new Player(Player_id::PLAYER_3, "player_3");
          
      //assumed to be correct
      player2->set_has_won(true);
    
      //assumed to be correct
      game_controller.get_game_state()->add_Players(player0);
      game_controller.get_game_state()->add_Players(player1);
      game_controller.get_game_state()->add_Players(player2);	
              
      game_controller.get_game_state()->set_current_player(Player_id::PLAYER_1);    
    }

    /* Any object and subroutine declared here can be accessed in the tests */
    Game_Controller game_controller;
    Player* player3 = new Player(Player_id::PLAYER_4, "player_4");

};

//const std::pair<Player_id, Player_id> GetNextPlayer_values = {{PLAYER_0, PLAYER_1}, {PLAYER_1, PLAYER_0}};

TEST_F(Game_StateTest, GetNextPlayer1) 
{
    //uses has_won maybe test first
    Player_id next_player = game_controller.get_next_player(Player_id::PLAYER_1);
    Player_id expected_next_player = Player_id::PLAYER_2;
    EXPECT_EQ(expected_next_player, next_player);
}



TEST_F(Game_StateTest, GetNextPlayer2)
{
  Player_id next_player = game_controller.get_next_player(Player_id::PLAYER_2);
  Player_id expected_next_player = Player_id::PLAYER_1;
  EXPECT_EQ(expected_next_player, next_player);
  
}

TEST_F(Game_StateTest, PlayerId)
{
  Player_id player3_Id = player3->get_player_id();
  Player_id expected_player3_Id = Player_id::PLAYER_4;
  EXPECT_EQ(expected_player3_Id, player3_Id);
  
}

TEST_F(Game_StateTest, CurrentPlayer)
{
  Player_id current_player = game_controller.get_game_state()->get_current_player();
  Player_id expected_current_player = Player_id::PLAYER_1;
  EXPECT_EQ(expected_current_player, current_player);
  
}

// testing action SKIP
// works 
TEST_F(Game_StateTest, SwitchPlayer)
{
  game_controller.switch_player(Player_id::PLAYER_1);
  Player_id next_player = game_controller.get_game_state()->get_current_player();
  Player_id expected_next_player = Player_id::PLAYER_2;
  EXPECT_EQ(expected_next_player, next_player);
}

// TODO does NOT work
TEST_F(Game_StateTest, SwitchPlayerExtended)
{
  Player_id next_player_id = game_controller.get_next_player(Player_id::PLAYER_1);
  game_controller.switch_player(next_player_id);
  Player_id next_player = game_controller.get_game_state()->get_current_player();
  Player_id expected_next_player = Player_id::PLAYER_3;
  EXPECT_EQ(expected_next_player, next_player);
}

// testing action REVERSE
TEST_F(Game_StateTest, Reverse)
{
  
  //std::vector<std::pair<Player_id, Player*> >& players = game_controller.get_game_state()->get_players();
  //reverse order of vec players
  std::reverse(game_controller.get_game_state()->get_players().begin(), game_controller.get_game_state()->get_players().end());
  
  //change current_player
  Player_id player_id = game_controller.get_game_state()->get_current_player();
  game_controller.switch_player(player_id);

  
  Player_id next_player = game_controller.get_game_state()->get_current_player();
  Player_id expected_next_player = Player_id::PLAYER_3; // start in SetUp() at 1 and reverse should be 3
  EXPECT_EQ(expected_next_player, player_id);
}



//INSTANTIATE_TEST_SUITE(GetNextPlayer, Game_ControllerTest, testing::ValuesIn(GetNextPlayer_values));

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

