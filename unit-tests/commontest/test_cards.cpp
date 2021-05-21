/*         UNIT TESTING
in command line :
--gtest_repeat=1000   // repeat the same test thousands of times
--gtest_break_on_failure   // debugger invoked at first failure
--gtest_output="xml:<fileName>"  // generating an xml report
*/

#include <gtest/gtest.h>
#include "./../../include/common/cards.hpp"
#include "./../../include/client/player_state.hpp"
#include "../../include/server/game_controller.hpp"
#include "../../include/server/game_state.hpp"


// test if the function Game_Controller::valid_move(); respects the UNO rules
// ----- a test fixture for every type of card on top of the discard pile.
// ----- a unit test for every type of card played on top of the discard pile.
//----------------------------------------------------------------------------------
class CardsTest : public ::testing::Test {

// protected: only accessible by derived class
protected:
		virtual void SetUp(){   
			// initialize a Discard_Pile Pile (typedef Discard_Pile Pile) with one card
			std::list<ck_Cards::Cards> discard_card_list = {ck_Cards::Cards::GREEN_0};
			ck_Cards::Discard_Pile* discard_pile = new ck_Cards::Pile::Pile(std::list<ck_Cards::Cards> discard_card_list);
			
			// push_back a given card to the pile
			// top of discard pile : ck_Cards::Cards::RED_5_A
			ck_Cards::Pile::push(ck_Cards::Cards::RED_5_A);
		}
		
		// ressource clean up
		// dynamic memory allocation performed manually with new must be freed with delete
		~CardsTest{
			delete discard_pile;
		}

		/* Any object and subroutine declared here can be accessed with the macro TEST_F() */
		ck_Cards::Discard_Pile discard_pile;
};

// TEST_F (TestFixtureName, UnitTestName) { can access game_controller declared in fixture Game_StateTest}
TEST_F(CardsTest, WrongColorWrongNumber) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::GREEN_2_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, WrongColorCorrectNumber) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::GREEN_5_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, CorrectColorWrongNumber) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::RED_4_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, Wild) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, WildDraw4) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_DRAW4_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, CorrectColorDraw2) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::RED_DRAW2_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, WrongColorDraw2) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::BLUE_DRAW2_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, CorrectColorReverse) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::RED_REVERSE_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, WrongColorReverse) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::BLUE_REVERSE_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, CorrectColorSkip) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::RED_SKIP_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest, WrongColorSkip) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::BLUE_SKIP_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

//----------------------------------------------------------------------------------
class CardsTest_SKIP : public ::testing::Test {

// protected: only accessible by derived class
protected:
		virtual void SetUp() 
		{   
			// initialize a Discard_Pile Pile (typedef Discard_Pile Pile) with one card
			std::list<ck_Cards::Cards> discard_card_list = {ck_Cards::Cards::GREEN_0};
			ck_Cards::Discard_Pile* discard_pile = new ck_Cards::Pile::Pile(std::list<ck_Cards::Cards> discard_card_list); 
			
			// push_back a given card to the pile
			ck_Cards::Pile::push(ck_Cards::Cards::YELLOW_SKIP_A);
		}
		
		// ressource clean up
		// dynamic memory allocation performed manually with new must be freed with delete
		~CardsTest_SKIP{
			delete discard_pile;
		}

		/* Any object and subroutine declared here can be accessed with the macro TEST_F() */
		ck_Cards::Discard_Pile discard_pile;
};

TEST_F(CardsTest_SKIP, CorrectAction) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::GREEN_SKIP_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_SKIP, WrongActionWrongColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::BLUE_REVERSE_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_SKIP, CorrectColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::YELLOW_8_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_SKIP, Wild) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_SKIP, Wild_Draw4) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_DRAW4_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

//----------------------------------------------------------------------------------
class CardsTest_REVERSE : public ::testing::Test {

// protected: only accessible by derived class
protected:
		virtual void SetUp() 
		{   
			// initialize a Discard_Pile Pile (typedef Discard_Pile Pile) with one card
			std::list<ck_Cards::Cards> discard_card_list = {ck_Cards::Cards::GREEN_0};
			ck_Cards::Discard_Pile* discard_pile = new ck_Cards::Pile::Pile(std::list<ck_Cards::Cards> discard_card_list);
			
			// push_back a given card to the pile
			ck_Cards::Pile::push(ck_Cards::Cards::GREEN_REVERSE_A);
		}
				
		// ressource clean up
		// dynamic memory allocation performed manually with new must be freed with delete
		~CardsTest_REVERSE{
			delete discard_pile;
		}

		/* Any object and subroutine declared here can be accessed with the macro TEST_F() */
		ck_Cards::Discard_Pile discard_pile;
};

TEST_F(CardsTest_REVERSE, CorrectAction) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::YELLOW_REVERSE_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_REVERSE, WrongActionWrongColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::YELLOW_DRAW2_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_REVERSE, CorrectColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::GREEN_2_B;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_REVERSE, Wild) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_REVERSE, Wild_Draw4) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_DRAW4_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

//----------------------------------------------------------------------------------
class CardsTest_DRAW_2 : public ::testing::Test {

// protected: only accessible by derived class
protected:
		virtual void SetUp() 
		{   
			// initialize a Discard_Pile Pile (typedef Discard_Pile Pile) with one card
			std::list<ck_Cards::Cards> discard_card_list = {ck_Cards::Cards::GREEN_0};
			ck_Cards::Discard_Pile* discard_pile = new ck_Cards::Pile::Pile(std::list<ck_Cards::Cards> discard_card_list);
			
			// push_back a given card to the pile
			ck_Cards::Pile::push(ck_Cards::Cards::BLUE_DRAW2_A);
		}
				
		// ressource clean up
		// dynamic memory allocation performed manually with new must be freed with delete
		~CardsTest_DRAW_2{
			delete discard_pile;
		}

		/* Any object and subroutine declared here can be accessed with the macro TEST_F() */
		ck_Cards::Discard_Pile discard_pile;
};

TEST_F(CardsTest_DRAW_2, CorrectAction) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::YELLOW_DRAW2_B;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_DRAW_2, WrongActionWrongColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::BLUE_REVERSE_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_DRAW_2, CorrectColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::BLUE_7_B;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_DRAW_2, Wild) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(CardsTest_DRAW_2, Wild_Draw4) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_DRAW4_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

//----------------------------------------------------------------------------------
class CardsTest_WILD : public ::testing::Test {
// protected: only accessible by derived class
	protected:
		virtual void SetUp() 
		{   			
			// initialize a Discard_Pile Pile (typedef Discard_Pile Pile) with one card
			std::list<ck_Cards::Cards> discard_card_list = {ck_Cards::Cards::GREEN_0};
			ck_Cards::Discard_Pile* discard_pile = new ck_Cards::Pile::Pile(std::list<ck_Cards::Cards> discard_card_list);
			
			// push_back a given card to the pile
			ck_Cards::Pile::push(ck_Cards::Cards::WILD_A);
			
			// after a wild card, if user would choose BLUE
			ck_Cards::Color color_to_be_matched = Game_State::set_color_to_be_matched(BLUE);
		}
			
		// ressource clean up
		// dynamic memory allocation performed manually with new must be freed with delete
		~CardsTest_WILD{
			delete discard_pile;
		}

		/* Any object and subroutine declared here can be accessed with the macro TEST_F() */
		ck_Cards::Color color_to_be_matched;
		ck_Cards::Discard_Pile discard_pile;
};

TEST_F(CardsTest_WILD, CorrectColor) 
{
	ck_Cards::Color attempt_color = BLUE;
	ck_Cards::Color correct_color = Game_State::get_color_to_be_matched();
	EXPECT_EQ(attempt_color, correct_color);
}

TEST_F(CardsTest_WILD, WrongColor) 
{
	ck_Cards::Color attempt_color = GREEN;
	ck_Cards::Color correct_color = Game_State::get_color_to_be_matched();
	EXPECT_EQ(attempt_color, correct_color);
}

//----------------------------------------------------------------------------------
class CardsTest_WILD_DRAW_4 : public ::testing::Test {
// protected: only accessible by derived class
	protected:
		virtual void SetUp() 
		{   			
			// initialize a Discard_Pile Pile (typedef Discard_Pile Pile) with one card
			std::list<ck_Cards::Cards> discard_card_list = {ck_Cards::Cards::GREEN_0};
			ck_Cards::Discard_Pile* discard_pile = new ck_Cards::Pile::Pile(std::list<ck_Cards::Cards> discard_card_list);
			
			// push_back a given card to the pile
			ck_Cards::Pile::push(ck_Cards::Cards::WILD_A);
			
			// after a wild card, if user would choose BLUE
			ck_Cards::Color color_to_be_matched = Game_State::set_color_to_be_matched(BLUE);
		}
			
		// ressource clean up
		// dynamic memory allocation performed manually with new must be freed with delete
		~CardsTest_WILD_DRAW_4{
			delete discard_pile;
		}

		/* Any object and subroutine declared here can be accessed with the macro TEST_F() */
		ck_Cards::Color color_to_be_matched;
		ck_Cards::Discard_Pile discard_pile;
};

TEST_F(CardsTest_WILD_DRAW_4, CorrectColor) 
{
	ck_Cards::Color attempt_color = BLUE;
	ck_Cards::Color correct_color = Game_State::get_color_to_be_matched();
	EXPECT_EQ(attempt_color, correct_color);
}

TEST_F(CardsTest_WILD_DRAW_4, WrongColor) 
{
	ck_Cards::Color attempt_color = GREEN;
	ck_Cards::Color correct_color = Game_State::get_color_to_be_matched();
	EXPECT_EQ(attempt_color, correct_color);
}

//---------------------------------------------------------------------------------
//INSTANTIATE_TEST_SUITE(GetNextPlayer, Game_ControllerTest, testing::ValuesIn(GetNextPlayer_values));
int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
