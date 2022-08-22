#ifndef COMMON_HPP
#define COMMON_HPP

#include <future>
#include <memory>
#include <queue>
#include <type_traits>
#include <vector>
#include <optional>
#include <sstream>
#include <exception>
#include <functional>
#include <algorithm>
#include <stack>
#include <random>
#include <list>
#include <chrono>
#include <atomic>
#include <thread>

#include "../../build/_deps/json-src/include/nlohmann/json.hpp"

#include "logger.hpp"

using namespace std::literals::chrono_literals;

//reimplementation of max because some macro is shadowing the std function
template<class T> 
[[nodiscard]] constexpr const T& MAX(const T& _a, const T& _b) noexcept {
    return (_a < _b) ? _b : _a;
};

enum class Player_id : uint32_t {
    NONE	    =	0,     
    PLAYER_1        =   1,
    PLAYER_2        =   2,
    PLAYER_3        =   3,
    PLAYER_4        =   4,
    PLAYER_ERROR    =   5
};

enum class State {
    FAILED      =   0, 
    SUCCESS     =   1,  
    ERROR_      =   2 //some flag shadows ERROR
};

enum class Request_Type : uint32_t {
	NEW_PLAYER = 0,
	PLAY_REQUEST = 1,
	DRAW_REQUEST = 2,
	EXIT_REQUEST = 3,
	START_GAME = 4,
	SELECTED_COLOR = 5
};

enum class Respond_Type: uint32_t {
    SUCCESFUL_CONNECTION = 0,
    SEND_HAND = 1,
    GAME_UPDATE = 2,
    ERROR_ = 3,
    SELECT_COLOR = 4,
    UNO = 5,
    START_NEW_GAME = 6,
    WINS = 7
};

class ckException : public std::exception {
    const std::string msg;
public:
    ckException(const std::string& _msg) noexcept : msg(_msg) {}
    [[nodiscard]] const char* what() const noexcept override { return msg.data(); }
};

#endif /* COMMON_HPP */
