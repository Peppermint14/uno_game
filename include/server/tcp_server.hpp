#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "../common/common.hpp"
#include "../common/network.hpp"

namespace net {

    using namespace std::literals::chrono_literals;
    using Logger = std::shared_ptr<spdlog::logger>;

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

        static void recieve(Player /*_player*/, std::function<void(const std::string&)> /*_callback*/);
        static void broadcast(const std::string& /*_msg*/);
        static void sendToPlayer(Player /*_player*/, const std::string /*_msg*/);

        template <class T>
        [[nodiscard]] static size_t getIdForPlayer(T _player) noexcept{
            const size_t id = static_cast<size_t>(_player);
            return idsForPlayer[id];
        }

        [[nodiscard]] static Player getPlayerForId(size_t _id) noexcept{
            for(size_t i = 1; i < 5; ++i)
                if(instance->idsForPlayer[i] == _id)
                    return static_cast<Player>(i);
            return Player::PLAYER_ERROR;
        }

    };

}

#endif /* TCP_SERVER_HPP */