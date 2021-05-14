#include "gtest/gtest.h"
#include "../../include/server/game_controller.hpp"
#include "./../../include/client/player_state.hpp"

//What is testing for an object????
//Thats our Test Fixture
// https://www.jetbrains.com/help/clion/unit-testing-tutorial.html#boost-test-framework test instead of Test
class Game_StateTest : public ::testing::test {

//why protected???? 
// protected: only accessible by derived class.
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
    
    // ressource clean up
    // dynamic memory allocation performed manually with new must be freed with delete
    ~Game_StateTest{
      delete player0;
      delete player1;
      delete player2;
    }

    /* Any object and subroutine declared here can be accessed with the macro TEST_F() */
    Game_Controller game_controller;   
};

//const std::pair<Player_id, Player_id> GetNextPlayer_values = {{PLAYER_0, PLAYER_1}, {PLAYER_1, PLAYER_0}};

// TEST_F (TestFixtureName, UnitTestName) { can access game_controller declared in fixture Game_StateTest}
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

//INSTANTIATE_TEST_SUITE(GetNextPlayer, Game_ControllerTest, testing::ValuesIn(GetNextPlayer_values));

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}