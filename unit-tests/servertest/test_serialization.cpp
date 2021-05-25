#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

//void Game_Controller::eval_request(const Player_id& player_id, const std::string& msg)
//   auto vals = nlohmann::json::parse(_json);

//void player_controller::eval_response(const std::string& msg)
//   nlohmann::json response = nlohmann::json::parse(msg);

class Serialization : public ::testing::Test {

  /* Any object and subroutine declared here can be accessed in the tests */
  //const std::string& msg = "PLAY_REQUEST";
};


TEST_F(Serialization, SerializeDeserialize) 
{
    // message to be parsed
    const std::string& msg = "PLAY_REQUEST";
    //serialize from msg to json
    nlohmann::json msg_json = nlohmann::json::parse(msg);
    //deserialize from json to msg
    auto msg_back = nlohmann::json::parse(msg_json);
    
    EXPECT_EQ(msg, msg_back);
}

//TEST_F(Serialization, IncorrectString) { }
/* from LAMA project
TEST(CardTest, SerializationException) {
  rapidjson::Document json = rapidjson::Document(rapidjson::kObjectType);
  json.Parse("not json");
  EXPECT_THROW(card::from_json(json), LamaException);
}
*/


int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}