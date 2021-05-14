#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include "../common/common.hpp"
#include "../common/utils.hpp"

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_acceptor.h>

namespace net {

    class TCP_Client {

        bool isInit = false;

        std::future<void> listener;
        std::optional<std::future<void>> connection;
        //std::vector<std::optional<std::future<void>>> connections;
        util::atomwrapper<bool> shutdown;
        //std::vector<util::atomwrapper<bool>> shutdown;
        std::atomic<bool> client_shutdown = false;

        static TCP_Client* instance;
        TCP_Client() noexcept;
        ~TCP_Client() noexcept;
        TCP_Client(const TCP_Client&) noexcept = delete;

        std::unique_ptr<util::BlockQueue<std::string>> sendQueue;
        //std::vector<std::unique_ptr<util::BlockQueue<std::string>>> sendQueue;
        util::BlockQueue<std::pair<Player_id, std::string>> cbQueue;

        std::function<void(Player_id, const std::string&)> cb = 0;
        
    public:
        static void terminate() noexcept;
        static void barrier() noexcept;
        static void disconect() noexcept;
        static void send(const std::string /*_msg*/);

        template <class Port, class Callback>
        static void init(Port _port, Callback _callback){
            if(instance->isInit) throw new ckException("TCP_Server already initialised");
            instance->isInit = true;
            instance->cb = _callback;
            auto logger = Logger::create("client_main");
            logger->info("Welcome. Initializing client...");
            instance->listener = std::async(std::launch::async, [port = _port, callback = _callback] {
                auto logger = Logger::create("client_listener");
                sockpp::socket_initializer sockInit;
                sockpp::tcp_acceptor acc(port);
                if (!acc) {
                    logger->error("Error opening acceptor: {}", acc.last_error_str());
                    throw new ckException(acc.last_error_str());
                }

                logger->info("Socket open and listening on port {}", port);

                while (!instance->client_shutdown) {
                    sockpp::tcp_socket sock = acc.accept();
                    sock.read_timeout(0.25s);
                    sock.write_timeout(0.25s);
                    sock.set_non_blocking(true);

                    if (!sock) {
                        logger->error("Error accepting incoming connection: {}", acc.last_error_str());
                    } else {
                        bool er = true;
                        for (size_t i = 0; i < 4; ++i) {
                            if (instance->connection.has_value()) continue;
                            er = false;
                            instance->connection = {std::async(std::launch::async, [id =0, instance = instance, sock = std::move(sock)]() mutable {
                                char buf[1024];
                                std::queue<char> msg;
                                std::queue<char> curMsg;

                                using clock = std::chrono::high_resolution_clock;
                                std::stringstream ss;
                                //ss << "server_player_" << id+1;
				ss<<"client_server"
                                auto logger = Logger::create(ss.str());

                                //notify the connection of a new player
                                /*
                                nlohmann::json cmsg;
                                cmsg["type"] = "new_player";
                                cmsg["id"] = id + 1;
                                instance->cbQueue.push({static_cast<Player_id>(id+1), cmsg.dump()});
                                */
                                
                                while (!instance->shutdown._a) {
                                    auto now = clock::now();

                                    //send
                                    {
                                        auto& q = instance->sendQueue;
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
                                                    instance->cbQueue.push( {message} );
                                                    //instance->cbQueue.push( {static_cast<Player_id>(id+1),message} );
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
                                instance->connection.reset();
                            })};
                            
                            //nlohmann::json msg;
                            //msg["id"] = i+1;
                            //TCP_Client::send(msg.dump());
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
