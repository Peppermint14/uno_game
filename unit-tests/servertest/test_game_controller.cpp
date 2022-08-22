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
		game_controller.get_game_state()->set_color_to_be_matched(ck_Cards::Color::RED);
	}
	 
	Game_Controller game_controller;
	//Discard_Pile discard_pile;
};

const std::vector<std::pair<ck_Cards::Cards, bool> > played_cards = {
  {ck_Cards::Cards::YELLOW_1_A,0},
  {ck_Cards::Cards::YELLOW_5_B,1},
  {ck_Cards::Cards::BLUE_6_A,0},
  {ck_Cards::Cards::BLUE_5_B,1},
  {ck_Cards::Cards::GREEN_2_B,0},
  {ck_Cards::Cards::GREEN_5_A,1},
  {ck_Cards::Cards::RED_4_B,1},
  {ck_Cards::Cards::WILD_A,1},
  {ck_Cards::Cards::RED_DRAW2_B,1},
  {ck_Cards::Cards::BLUE_DRAW2_A,0},
  {ck_Cards::Cards::RED_REVERSE_B,1},
  {ck_Cards::Cards::BLUE_REVERSE_A,0},
  {ck_Cards::Cards::RED_SKIP_A,1},
  {ck_Cards::Cards::BLUE_SKIP_A,0}
};

// Testing the function valid_move() with all colors, all actions, 
// and with or without the same value (5) as the top card of the discard pile.
// valid_move() returns a boolean telling if a certain card can be played on the top card of the discard pile.
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

        // initializing the game_state with the three above players
        game_controller.get_game_state()->add_Players(player0);
        game_controller.get_game_state()->add_Players(player1);
        game_controller.get_game_state()->add_Players(player2);

        // assigning a specific hand to every three players
        game_controller.get_game_state()->get_player(Player_id::PLAYER_1)->get_hand().push({Cards::RED_DRAW2_A, Cards::BLUE_SKIP_A, Cards::GREEN_0});

        game_controller.get_game_state()->get_player(Player_id::PLAYER_2)->get_hand().push({Cards::RED_4_B, Cards::RED_REVERSE_B, Cards::RED_SKIP_B});

        game_controller.get_game_state()->get_player(Player_id::PLAYER_3)->get_hand().push({Cards::RED_4_A, Cards::RED_REVERSE_A, Cards::RED_SKIP_A});

        // setting the game state such that it is player_1 's turn
        game_controller.get_game_state()->set_current_player(Player_id::PLAYER_1);

        // setting up the discard pile
        std::list<ck_Cards::Cards> discard_pile_list = {
                ck_Cards::Cards::GREEN_1_A,ck_Cards::Cards::BLUE_SKIP_A, ck_Cards::Cards::RED_0};
        ck_Cards::Discard_Pile discard_pile;
        ck_Cards::Draw_Pile draw_pile;
        discard_pile.push(discard_pile_list);
        discard_pile.push(ck_Cards::Cards::BLUE_0);
        game_controller.get_game_state()->set_discard_pile(discard_pile);
        game_controller.get_game_state()->set_draw_pile(draw_pile);
        game_controller.get_game_state()->set_color_to_be_matched(Color::BLUE);
    }

    // Any object and subroutine declared here can be accessed in the following tests
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

// testing action SKIP with function switch_player()
// should iterate the current_player to the next
TEST_F(Game_State_Test, SwitchPlayer)
{
    game_controller.switch_player(Player_id::PLAYER_1);
    Player_id next_player = game_controller.get_game_state()->get_current_player();
    Player_id expected_next_player = Player_id::PLAYER_2;
    EXPECT_EQ(expected_next_player, next_player);
}

// testing implementation of action REVERSE
// as implemented in Game_Controller::effect_of_card()
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

// check reshuffling of draw_pile
TEST_F(Game_State_Test, Reshuffle_DrawPile)
{
    size_t expected_size_draw_pile = game_controller.get_game_state()->get_discard_pile().size() -2;
    game_controller.draw_card(Player_id::PLAYER_1);
    size_t actual_size_draw_pile = game_controller.get_game_state()->get_draw_pile().size();
    EXPECT_EQ(expected_size_draw_pile, actual_size_draw_pile);
}

// testing if the played card transmitted with msg_json to the function eval_request()
// is arrived on top of the discard pile
TEST_F(Game_State_Test, Update_discard_pile)
{
    //game_controller.get_game_state()->get_discard_pile().push(Cards::BLUE_5_A);
    //game_controller.get_game_state()->set_color_to_be_matched(Color::BLUE);
    nlohmann::json msg_json;
    msg_json["type"]= Request_Type::PLAY_REQUEST;
    msg_json["card"]=Cards::BLUE_SKIP_A;
    msg_json["id"]=1;

    game_controller.eval_request(Player_id::PLAYER_1, msg_json.dump());

    const Cards topCard = game_controller.get_game_state()->get_discard_pile().get_top_card();
    const Cards expected_topCard = Cards::BLUE_SKIP_A;
    EXPECT_EQ(expected_topCard, topCard);
}

//check if draw_2 cards adds two cards to the hand of the next player
TEST_F(Game_State_Test, Draw2)
{
    // player1 plays a red draw2 card on top of the red discard pile
    nlohmann::json msg_json;
    msg_json["type"]= Request_Type::PLAY_REQUEST;
    msg_json["id"]=1;
    msg_json["card"]=Cards::BLUE_DRAW2_A;

    game_controller.eval_request(Player_id::PLAYER_1, msg_json.dump());

    //game_controller.draw_card(Player_id::PLAYER_2);

    // player2 will get 2 extra cards, going from 3 to 5
    const size_t nbCards = game_controller.get_game_state()->get_player(Player_id::PLAYER_2)->number_of_cards();
    const size_t expected_nbCards = 5;
    EXPECT_EQ(expected_nbCards, nbCards);
}

//check if color_to_be_matched in the game state is correctly updated
TEST_F(Game_State_Test, UpdateColor)
{
    //game_controller.get_game_state()->get_discard_pile().push(Cards::GREEN_5_B);

    nlohmann::json msg_json;
    msg_json["type"]= Request_Type::PLAY_REQUEST;
    msg_json["id"]=1;
    msg_json["card"]=Cards::GREEN_0;

    game_controller.eval_request(Player_id::PLAYER_1, msg_json.dump());

    Color color = game_controller.get_game_state()->get_color_to_be_matched();
    Color expected_color = Color::GREEN;
    EXPECT_EQ(expected_color, color);
}

//check reshuffling of draw_pile
// testing implementation of function number_of_cards()
TEST_F(Game_State_Test, NumberOfCards)
{
    const size_t nbCards = game_controller.get_game_state()->get_player(Player_id::PLAYER_1)->number_of_cards();
    const size_t expected_nbCards = 3;
    EXPECT_EQ(expected_nbCards, nbCards);
}

// testing if function clear() empties the players hand
TEST_F(Game_State_Test, ClearHand)
{
    game_controller.get_game_state()->get_player(Player_id::PLAYER_2)->get_hand().clear();
    const size_t nbCards = game_controller.get_game_state()->get_player(Player_id::PLAYER_2)->number_of_cards();
    const size_t expected_nbCards = 0;
    EXPECT_EQ(expected_nbCards, nbCards);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}