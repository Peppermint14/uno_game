/*         UNIT TESTING
in command line :
--gtest_repeat=1000   // repeat the same test thousands of times
--gtest_break_on_failure   // debugger invoked at first failure
--gtest_output="xml:<fileName>"  // generating an xml report
*/

#include "gtest/gtest.h"
#include "./../../include/common/cards.hpp"
#include "./../../include/client/player_state.hpp"
#include "../../include/server/game_controller.hpp"


// test if the function Game_Controller::valid_move(); respects the UNO rules

class CardsTest : public ::testing::test {

// protected: only accessible by derived class
protected:
		virtual void SetUp() 
		{   
			// initialize a Discard_Pile Pile (typedef Discard_Pile Pile) with one card
			std::list<ck_Cards::Cards> discard_card_list = {ck_Cards::Cards::GREEN_0};
			ck_Cards::Discard_Pile* discard_pile = new ck_Cards::Pile::Pile(std::list<ck_Cards::Cards> discard_card_list); 
		}
		
		virtual void topDiscardPile(){
			// push_back a given card to the pile
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

//---------------------- testing UNO rule ---------------------------------------
//---------------------- playing an allowed card (color, action, value) ---------

// TEST_F (TestFixtureName, UnitTestName) { can access game_controller declared in fixture Game_StateTest}
// top of discard pile : ck_Cards::Cards::RED_5_A

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

//---------------------- testing UNO rule ---------------------------------------
//---------------------- after an action card -----------------------------------
class DiscardPile_SKIP : CardsTest {
private:
	virtual void topDiscardPile(){
		// push_back a given card to the pile
		ck_Cards::Pile::push(ck_Cards::Cards::YELLOW_SKIP_A);
	}
};

TEST_F(DiscardPile_SKIP, CorrectAction) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::GREEN_SKIP_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_SKIP, WrongActionWrongColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::BLUE_REVERSE_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_SKIP, CorrectColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::YELLOW_8_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_SKIP, Wild) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_SKIP, Wild_Draw4) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_DRAW4_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

//-------------------------------------------------
class DiscardPile_REVERSE : CardsTest {
private:
	virtual void topDiscardPile(){
		// push_back a given card to the pile
		ck_Cards::Pile::push(ck_Cards::Cards::GREEN_REVERSE_A);
	}
};

TEST_F(DiscardPile_REVERSE, CorrectAction) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::YELLOW_REVERSE_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_REVERSE, WrongActionWrongColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::YELLOW_DRAW2_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_REVERSE, CorrectColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::GREEN_2_B;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_REVERSE, Wild) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_REVERSE, Wild_Draw4) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_DRAW4_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

//--------------------------------------------------
class DiscardPile_DRAW_2 : CardsTest {
private:
	virtual void topDiscardPile(){
		// push_back a given card to the pile
		ck_Cards::Pile::push(ck_Cards::Cards::BLUE_DRAW2_A);
	}
};

TEST_F(DiscardPile_DRAW_2, CorrectAction) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::YELLOW_DRAW2_B;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_DRAW_2, WrongActionWrongColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::BLUE_REVERSE_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 0;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_DRAW_2, CorrectColor) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::BLUE_7_B;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_DRAW_2, Wild) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

TEST_F(DiscardPile_DRAW_2, Wild_Draw4) 
{
	const ck_Cards::Cards& card = ck_Cards::Cards::WILD_DRAW4_A;
	bool obtained_valid_move = Game_Controller::valid_move(card);
	bool expected_valid_move = 1;
	EXPECT_EQ(expected_valid_move, obtained_valid_move);
}

//--------------------------------------------------
class DiscardPile_WILD : CardsTest {
private:
	virtual void topDiscardPile(){
		// push_back a given card to the pile
		ck_Cards::Pile::push(ck_Cards::Cards::WILD_B);
	}
	
	// TODO modify base class to add game state
	// or do these tests in servertest/
	//ck_Cards::Color chosenColor = Game_State::get_color_to_be_matched();
};


//---------------------------------------------------
class DiscardPile_WILD_DRAW4 : CardsTest {
private:
	virtual void topDiscardPile(){
		// push_back a given card to the pile
		ck_Cards::Pile::push(ck_Cards::Cards::WILD_DRAW4_B);
	}
	
	// TODO modify base class to add game state
	// or do these tests in servertest/
	ck_Cards::Color chosenColor = Game_State::get_color_to_be_matched();

};

//---------------------------------------------------------------------------------
//INSTANTIATE_TEST_SUITE(GetNextPlayer, Game_ControllerTest, testing::ValuesIn(GetNextPlayer_values));
int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
