#ifndef NETWORK_HPP
#define NETWORK_HPP

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

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_acceptor.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace net {

    using namespace std::literals::chrono_literals;
    using Logger = std::shared_ptr<spdlog::logger>;

    namespace detail {

        enum class Player : uint32_t {
            PLAYER_ERROR    =   0,
            PLAYER_1        =   1,
            PLAYER_2        =   2,
            PLAYER_3        =   3,
            PLAYER_4        =   4       
        };

        class TCPException : public std::exception {
            const std::string msg;
        public:
            TCPException(const std::string& _msg) noexcept : msg(_msg) {}
            const char* what() const noexcept override { return msg.data(); }
        };

        template<class T> 
        [[nodiscard]] constexpr const T& MAX(const T& _a, const T& _b) noexcept {
            return (_a < _b) ? _b : _a;
        };
    }

    class TCP_Server {

        bool isInit = false;
        Logger logger;

        std::future<void> listener;
        std::vector<std::optional<std::future<void>>> connections;
        bool shutdown =  false;
        std::vector<size_t> idsForPlayer;

        static TCP_Server* instance;
        TCP_Server() noexcept;
        ~TCP_Server() noexcept;
        TCP_Server(const TCP_Server&) noexcept = delete;

        std::vector<std::mutex> m_sendQueue;
        std::vector<std::queue<std::string>> sendQueue;

        std::vector<std::mutex> m_callbacks;
        std::vector<std::function<void(const std::string&)>> callbacks;
        
    public:

        static void init(Logger /*_logger*/, uint32_t /*_port*/);

        static void recieve(detail::Player /*_player*/, std::function<void(const std::string&)> /*_callback*/);
        static void broadcast(const std::string& /*_msg*/);
        static void sendToPlayer(detail::Player /*_player*/, const std::string /*_msg*/);

        template <class T>
        [[nodiscard]] static size_t getIdForPlayer(T _player) noexcept{
            const size_t id = static_cast<size_t>(_player);
            return idsForPlayer[id];
        }

        [[nodiscard]] static detail::Player getPlayerForId(size_t _id) noexcept{
            for(size_t i = 1; i < 5; ++i)
                if(instance->idsForPlayer[i] == _id)
                    return static_cast<detail::Player>(i);
            return detail::Player::PLAYER_ERROR;
        }

    };




    class TCP_Client {

    public:
        static void connect(Logger /*_logger*/, const std::string& /*adress*/);
    };

}

#endif /* NETWORK_HPP */