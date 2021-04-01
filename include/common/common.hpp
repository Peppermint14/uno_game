#ifndef COMMON_HPP
#define COMMON_HPP

#include <future>
#include <memory>
#include <queue>
#include <chrono>
#include <type_traits>
#include <vector>
#include <optional>
#include <sstream>
#include <exception>
#include <functional>
#include <algorithm>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

//reimplementation of max because some macro is shadowing the std function
template<class T> 
[[nodiscard]] constexpr const T& MAX(const T& _a, const T& _b) noexcept {
    return (_a < _b) ? _b : _a;
};

enum class Player : uint32_t {
    PLAYER_ERROR    =   0,
    PLAYER_1        =   1,
    PLAYER_2        =   2,
    PLAYER_3        =   3,
    PLAYER_4        =   4       
};

enum class Cards : uint32_t {

};

enum class Color : uint32_t {
    GREEN   =   0,
    RED     =   1,
    YELLOW  =   2,
    BLUE    =   3
};

enum class State {
    FAILED, SUCCESS, ERROR
};

#endif /* COMMON_HPP */