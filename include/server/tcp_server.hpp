#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "../common/common.hpp"
#include "../common/utils.hpp"

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_acceptor.h>
#include <thread>
#include <functional>
#include <unordered_map>
#include <shared_mutex>


/*
class server_network_manager {
private:

    inline static server_network_manager* _instance;
    inline static std::shared_mutex _rw_lock;
    inline static sockpp::tcp_acceptor _acc;

    inline static std::unordered_map<std::string, std::string> _player_id_to_address;
    inline static std::unordered_map<std::string, sockpp::tcp_socket> _address_to_socket;

    void connect(const std::string& url, const uint16_t  port);

    static void listener_loop();
    static void read_message(sockpp::tcp_socket socket,
                             const std::function<void(const std::string&, const sockpp::tcp_socket::addr_t&)>& message_handler);
    static void handle_incoming_message(const std::string& msg, const sockpp::tcp_socket::addr_t& peer_address);
    static ssize_t send_message(const std::string& msg, const std::string& address);
public:
    server_network_manager();
    ~server_network_manager();

    // Used to broadcast a server_response (e.g. a full_state_response) to all 'players' except 'exclude'
    static void broadcast_message(std::string& msg/* , const std::vector<player*>& players, const player* exclude);

    static void on_player_left(std::string player_id);
};


*/



namespace net {

    class TCP_Server {

        bool isInit = false;

        std::future<void> listener;
        std::vector<std::optional<std::future<void>>> connections;
        std::vector<util::atomwrapper<bool>> shutdown;
        std::atomic<bool> server_shutdown = false;

        static TCP_Server* instance;
        TCP_Server() noexcept;
        ~TCP_Server() noexcept;
        TCP_Server(const TCP_Server&) noexcept = delete;

        std::vector<std::unique_ptr<util::BlockQueue<std::string>>> sendQueue;
        util::BlockQueue<std::pair<Player_id, std::string>> cbQueue;

        std::function<void(Player_id, const std::string&)> cb = 0;
        
    public:
        static void terminate() noexcept;
        static void barrier() noexcept;
        static void disconect(Player_id) noexcept;
        static void broadcast(const std::string& /*_msg*/);
        static void sendToPlayer(Player_id /*_player*/, const std::string /*_msg*/);

        template <class Port, class Callback>
        static void init(Port _port, Callback _callback){
            if(instance->isInit) throw new ckException("TCP_Server already initialised");
            instance->isInit = true;
            instance->cb = _callback;
            auto logger = Logger::create("server_main");
            logger->info("Welcome. Initializing server...");
            instance->listener = std::async(std::launch::async, [port = _port, callback = _callback] {
                auto logger = Logger::create("server_listener");
                sockpp::socket_initializer sockInit;
                sockpp::tcp_acceptor acc(port);
                if (!acc) {
                    logger->error("Error opening acceptor: {}", acc.last_error_str());
                    throw new ckException(acc.last_error_str());
                }

                logger->info("Socket open and listening on port {}", port);

                while (!instance->server_shutdown) {
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
                            instance->connections[i] = {std::async(std::launch::async, [id = i, instance = instance, sock = std::move(sock)]() mutable {
                                char buf[1024];
                                std::queue<char> msg;
                                std::queue<char> curMsg;

                                using clock = std::chrono::high_resolution_clock;
                                std::stringstream ss;
                                ss << "server_player_" << id+1;
                                auto logger = Logger::create(ss.str());

                                //notify the connection of a new player
                                /*
                                nlohmann::json cmsg;
                                cmsg["type"] = "new_player";
                                cmsg["id"] = id + 1;
                                instance->cbQueue.push({static_cast<Player_id>(id+1), cmsg.dump()});
                                */
                                
                                while (!instance->shutdown[id]._a) {
                                    auto now = clock::now();

                                    //send
                                    {
                                        auto& q = instance->sendQueue[id];
                                        while (!q->empty()) {
                                            std::string msg_ = q->front();
                                            msg_.push_back(static_cast<char>(3));
                                            if(sock.write(msg_) == 1)
                                                logger->error("Send failed: {}", msg_);
                                            else{
                                                logger->debug("Sent: {}", msg_);
                                                q->pop();
                                            }                                     
                                        }
                                    }

                                    //recieve
                                    {
                                        ssize_t n;
                                        
                                        while ((n = sock.read(buf, sizeof(buf))) > 0) {
                                            for (size_t i = 0; i < n; ++i)
                                                msg.push(buf[i]);
                                        }
                                        if (!msg.empty()) {
                                            //parse all containing messages in the buffer
                                            while(!msg.empty()){
                                                const char c = msg.front();
                                                msg.pop();
                                                //reached end of message
                                                if(c == static_cast<char>(3)){
                                                    std::string message;
                                                    message.reserve(curMsg.size());
                                                    while(!curMsg.empty()){
                                                        message.push_back(curMsg.front());
                                                        curMsg.pop();
                                                    }
                                                    logger->debug("Received: {}", message);
                                                    //callback(static_cast<Player>(id+1),message);
                                                    instance->cbQueue.push( {static_cast<Player_id>(id+1),message} );
                                                } else
                                                    curMsg.push(c);                                                
                                            }                                   
                                        }
                                    }
                                    //max 60 fps
                                    const auto delta = 16ms - std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - now);
                                    if(delta > 0ms) std::this_thread::sleep_for(delta);
                                }

                                sock.shutdown();
                                instance->connections[id].reset();
                            })};
                            
                            nlohmann::json msg;
                            msg["id"] = i;
                            msg["type"] = Respond_Type::ID_ASSIGN;
                            TCP_Server::sendToPlayer(static_cast<Player_id>(i+1), msg.dump());
                            break;
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






/*#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "../common/common.hpp"
#include "../common/utils.hpp"

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_acceptor.h>

namespace net {

    class TCP_Server {

        bool isInit = false;

        std::future<void> listener;
        std::vector<std::optional<std::future<void>>> connections;
        std::vector<util::atomwrapper<bool>> shutdown;
        std::atomic<bool> server_shutdown = false;

        static TCP_Server* instance;
        TCP_Server() noexcept;
        ~TCP_Server() noexcept;
        TCP_Server(const TCP_Server&) noexcept = delete;

        std::vector<std::unique_ptr<util::BlockQueue<std::string>>> sendQueue;
        util::BlockQueue<std::pair<Player_id, std::string>> cbQueue;

        std::function<void(Player_id, const std::string&)> cb = 0;
        
    public:
        static void terminate() noexcept;
        static void barrier() noexcept;
        static void disconect(Player_id) noexcept;
        static void broadcast(const std::string& /*_msg);
        static void sendToPlayer(Player_id /*_player, const std::string /*_msg);

        template <class Port, class Callback>
        static void init(Port _port, Callback _callback){
            if(instance->isInit) throw new ckException("TCP_Server already initialised");
            instance->isInit = true;
            instance->cb = _callback;
            auto logger = Logger::create("server_main");
            logger->info("Welcome. Initializing server...");
            instance->listener = std::async(std::launch::async, [port = _port, callback = _callback] {
                auto logger = Logger::create("server_listener");
                sockpp::socket_initializer sockInit;
                sockpp::tcp_acceptor acc(port);
                if (!acc) {
                    logger->error("Error opening acceptor: {}", acc.last_error_str());
                    throw new ckException(acc.last_error_str());
                }

                logger->info("Socket open and listening on port {}", port);

                while (!instance->server_shutdown) {
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
                            instance->connections[i] = {std::async(std::launch::async, [id = i, instance = instance, sock = std::move(sock)]() mutable {
                                char buf[1024];
                                std::queue<char> msg;
                                std::queue<char> curMsg;

                                using clock = std::chrono::high_resolution_clock;
                                std::stringstream ss;
                                ss << "server_player_" << id+1;
                                auto logger = Logger::create(ss.str());

                                //notify the connection of a new player
                                /*
                                nlohmann::json cmsg;
                                cmsg["type"] = "new_player";
                                cmsg["id"] = id + 1;
                                instance->cbQueue.push({static_cast<Player_id>(id+1), cmsg.dump()});
                                
                                
                                while (!instance->shutdown[id]._a) {
                                    auto now = clock::now();

                                    //send
                                    {
                                        auto& q = instance->sendQueue[id];
                                        while (!q->empty()) {
                                            std::string msg_ = q->front();
                                            msg_.push_back(static_cast<char>(3));
                                            if(sock.write(msg_) == 1)
                                                logger->error("Send failed: {}", msg_);
                                            else{
                                                logger->debug("Sent: {}", msg_);
                                                q->pop();
                                            }                                     
                                        }
                                    }

                                    //recieve
                                    {
                                        ssize_t n;
                                        
                                        while ((n = sock.read(buf, sizeof(buf))) > 0) {
                                            for (size_t i = 0; i < n; ++i)
                                                msg.push(buf[i]);
                                        }
                                        if (!msg.empty()) {
                                            //parse all containing messages in the buffer
                                            while(!msg.empty()){
                                                const char c = msg.front();
                                                msg.pop();
                                                //reached end of message
                                                if(c == static_cast<char>(3)){
                                                    std::string message;
                                                    message.reserve(curMsg.size());
                                                    while(!curMsg.empty()){
                                                        message.push_back(curMsg.front());
                                                        curMsg.pop();
                                                    }
                                                    logger->debug("Received: {}", message);
                                                    //callback(static_cast<Player>(id+1),message);
                                                    instance->cbQueue.push( {static_cast<Player_id>(id+1),message} );
                                                } else
                                                    curMsg.push(c);                                                
                                            }                                   
                                        }
                                    }
                                    //max 60 fps
                                    const auto delta = 16ms - std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - now);
                                    if(delta > 0ms) std::this_thread::sleep_for(delta);
                                }

                                sock.shutdown();
                                instance->connections[id].reset();
                            })};
                            
                            nlohmann::json msg;
                            msg["id"] = i+1;
                            TCP_Server::sendToPlayer(static_cast<Player_id>(i+1), msg.dump());
                            break;
                        }
                        if (er)
                            logger->error("cannot accept more connections");
                    }
                }
            });
        }

    };

}

#endif */ /* TCP_SERVER_HPP */
