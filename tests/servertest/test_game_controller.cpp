#include "gtest/gtest.h"
#include "../../include/server/game_controller.hpp"

//What is testing for an object????
//Thats our Test Fixture
class Game_StateTest : public ::testing::TestWithParam<std::pair<ck_Cards::Cards, bool>> {

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
	game_controller.get_game_state()->get_discard_pile().push(ck_Cards::Cards::RED_5_A);   
    }

    /* Any object and subroutine declared here can be accessed in the tests */
    	Game_Controller game_controller;   
};

//const std::pair<Player_id, Player_id> GetNextPlayer_values = {{PLAYER_0, PLAYER_1}, {PLAYER_1, PLAYER_0}};

const std::vector<std::pair<ck_Cards::Cards, bool>> tested_cards =  {
	{ck_Cards::Cards::GREEN_2_A,0},
	{ck_Cards::Cards::GREEN_5_A,1}
};


TEST_P(Game_StateTest, ValidMove)
{
	auto card_bool_pair = GetParam();
	bool obtained_valid_move = game_controller.valid_move(card_bool_pair.first);
	bool actual_valid_move = card_bool_pair.second;
	EXPECT_EQ(obtained_valid_move, actual_valid_move);
};


INSTANTIATE_TEST_SUITE_P(
  ValidMove,
  Game_StateTest,
  testing::ValuesIn(tested_cards));


/*

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
*/
