/*         UNIT TESTING

The grading of your test cases will contribute 1/6 to your final project grade.
The goal is to cover the state update behavior of your game.
Therefore, think of different scenarios that can occur in the game and use them as a starting point to design your unit tests.
Implement at least 15 unit tests, which cover the game state update functions of your game.
(If you follow the example project, these updates happen on the server side).

in command line :
--gtest_repeat=1000   // repeat the same test thousands of times
--gtest_break_on_failure   // debugger invoked at first failure
--gtest_output="xml:<fileName>"  // generating an xml report
*/

#include "gtest/gtest.h"
#include "./../../include/client/player_state.hpp"
#include "../../include/server/game_controller.hpp"


class Player_StateTest : public ::testing::test {

// protected: only accessible by derived class
protected:
		virtual void SetUp() 
		{   
			// create a new player
			Player* player0 = new Player(Player_id::PLAYER_1, "player_1");
			// currently playing
			player0.player_state->current_Player = Player_id::PLAYER_1;

			// with a hand of following cards
			std::list<ck_Cards::Cards> cardsList = {ck_Cards::Cards::BLUE_0, ck_Cards::Cards::BLUE_1_A, ck_Cards::Cards::BLUE_2_A, ck_Cards::Cards::BLUE_3_A};
			ck_Cards::Hand* handPlayer0 = new ck_Cards::Hand(cardsList);
			
			player0.player_state->hand = handPlayer0;
			player0.player_state->number_of_cards = cardsList.size();
			player0.player_state->players_turn = 1;
			player0.player_state->play_direction = 1;
			player0.player_state->player_won = 0;
			player0.player_state->player_quit = 0;
			
			// assume the top card of the discard pile is the following
			player0.player_state->top_discard = ck_Cards::Cards::RED_5_A;
			//assumed to be correct
			game_controller.get_game_state()->add_Players(player0);
			game_controller.get_game_state()->set_current_player(Player_id::PLAYER_1);    
		}
		
		// ressource clean up
		// dynamic memory allocation performed manually with new must be freed with delete
		~CardsTest{
			delete handPlayer0;
			delete player0;
		}

		/* Any object and subroutine declared here can be accessed with the macro TEST_F() */
		Player player0;
};

// TEST_F (TestFixtureName, UnitTestName) { can access game_controller declared in fixture Game_StateTest}

TEST_F(Player_StateTest, UnitTestName) 
{
	//obtained_
	//expected_
	//EXPECT_EQ(expected_, obtained_);
}


//INSTANTIATE_TEST_SUITE(GetNextPlayer, Game_ControllerTest, testing::ValuesIn(GetNextPlayer_values));

int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
