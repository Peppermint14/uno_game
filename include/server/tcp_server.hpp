#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "../common/common.hpp"

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_acceptor.h>

namespace net {

    class TCP_Server {

        bool isInit = false;

        std::future<void> listener;
        std::vector<std::optional<std::future<void>>> connections;
        std::atomic<bool> shutdown =  false;
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
     
        static void terminate() noexcept;
        static void barrier() noexcept;
        static void broadcast(const std::string& /*_msg*/);
        static void sendToPlayer(Player /*_player*/, const std::string /*_msg*/);
        static void recieve(Player /*_player*/, std::function<void(const std::string&)> /*_callback*/);

        template <class T>
        [[nodiscard]] static size_t getIdForPlayer(T _player) noexcept{
            constexpr size_t id = static_cast<size_t>(_player);
            return instance->idsForPlayer[id];
        }

        [[nodiscard]] static Player getPlayerForId(size_t _id) noexcept{
            for(size_t i = 1; i < 5; ++i)
                if(instance->idsForPlayer[i] == _id)
                    return static_cast<Player>(i);
            return Player::PLAYER_ERROR;
        }

        template <class Port, class Callback>
        static void init(Port _port, Callback _callback){
            if(instance->isInit) throw new ckException("TCP_Server already initialised");
            instance->isInit = true;
            auto logger = Logger::create("server_main");
            logger->info("Welcome. Initializing server...");
            instance->listener = std::async(std::launch::async, [port = _port, callback = _callback] {
                auto logger = Logger::create("server_listener");
                sockpp::tcp_acceptor acc(port);
                if (!acc) {
                    logger->error("Error opening acceptor: {}", acc.last_error_str());
                    throw new ckException(acc.last_error_str());
                }

                logger->info("Socket open and listening on port {}", port);

                while (!instance->shutdown) {
                    sockpp::tcp_socket sock = acc.accept();
                    sock.read_timeout(0.25s);
                    sock.write_timeout(0.25s);
                    sock.set_non_blocking(true);

                    if (!sock) {
                        logger->error("Error accepting incoming connection: {}", acc.last_error_str());
                    } else {
                        bool er = true;
                        for (size_t i = 0; i < 4; ++i) {
                            if (instance->connections[i].has_value()) continue;
                            er = false;
                            instance->connections[i] = {std::async(std::launch::async, [id = i, instance = instance, sock = std::move(sock), callback = callback]() mutable {
                                char buf[512];
                                using clock = std::chrono::high_resolution_clock;
                                std::stringstream ss;
                                ss << "server_player_" << id;
                                auto logger = Logger::create(ss.str());
                                while (!instance->shutdown) {
                                    auto now = clock::now();

                                    //send
                                    {
                                        std::queue<std::string>& q = instance->sendQueue[id];
                                        std::lock_guard<std::mutex> lock(instance->m_sendQueue[id]);
                                        while (!q.empty()) {
                                            const std::string msg = q.front();
                                            sock.write(msg);
                                            logger->debug("[Server] Sent: {}", msg);
                                            q.pop();
                                        }
                                    }

                                    //recieve
                                    {
                                        ssize_t n;
                                        std::vector<char> msg;
                                        while ((n = sock.read(buf, sizeof(buf))) > 0) {
                                            for (size_t i = 0; i < n; ++i)
                                                msg.push_back(buf[i]);
                                        }
                                        if (!msg.empty()) {
                                            std::string msg_st(msg.begin(), msg.end());
                                            logger->debug("[Server] Received: {}", msg_st);
                                            callback(static_cast<Player>(id+1), msg_st);
                                        }
                                    }
                                    //max 60 fps
                                    const auto delta = 16ms - std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - now);
                                    if(delta > 0ms) std::this_thread::sleep_for(delta);
                                }

                                sock.shutdown();
                            })};
                            
                            nlohmann::json msg;
                            msg["id"] = i;
                            TCP_Server::sendToPlayer(static_cast<Player>(i), msg.dump());
                        }
                        if (er)
                            logger->error("cannot accept more connections");
                    }
                }
            });
        }

    };

}

#endif /* TCP_SERVER_HPP */