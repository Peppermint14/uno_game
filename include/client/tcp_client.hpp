#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "../common/common.hpp"

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_connector.h>
#include <sockpp/inet_address.h>

namespace net {

    class TCP_Client {

        std::queue<std::string> toSend;
        std::mutex mutex;
        std::future<void> connection;
        std::atomic<bool> shutdown = false;
        bool isInit = false;

        static TCP_Client* instance;

        TCP_Client() noexcept {}

    public:

        static void send(const std::string&) noexcept;
        static void terminate() noexcept;
        static void barrier() noexcept;

        template<class T, class Func>
        static void connect(const std::string& _adress, T _port, Func _callback){
            if(instance->isInit) throw new ckException("TCP_Server already initialised");
            instance->isInit = true;
            auto logger = Logger::create("client_main");

            struct co{
                sockpp::socket_initializer sockInit;
                sockpp::tcp_connector conn;
            };
            std::unique_ptr<co> coptr = std::make_unique<co>();
            if (!coptr->conn.connect(sockpp::inet_address(_adress, _port))){
                logger->error("Error connecting: {}", coptr->conn.last_error_str());
                throw new ckException(coptr->conn.last_error_str());
            }
            coptr->conn.read_timeout(0.25s);
            coptr->conn.write_timeout(0.25s);
            coptr->conn.set_non_blocking(true);
            instance->connection = std::async(std::launch::async, [coptr = std::move(coptr), adress = _adress, port = _port, cb = _callback]() mutable {
                auto logger = Logger::create("client_thread");

                logger->info("connected to {} on port {}", adress, port);

                char buf[1024];
                std::queue<char> msg;
                std::queue<char> curMsg;

                using clock = std::chrono::high_resolution_clock;
                
                while (!instance->shutdown) {
                    auto now = clock::now();

                    //send
                    {
                        std::queue<std::string>& q = instance->toSend;
                        std::lock_guard<std::mutex> lock(instance->mutex);
                        while (!q.empty() && !instance->shutdown) {
                            std::string msg_ = q.front();
                             msg_.push_back(static_cast<char>(3));
                            if(coptr->conn.write(msg_) == 1)
                                logger->error("Send failed: {}", msg_);
                            else
                                logger->debug("Sent: {}", msg_);
                            q.pop();
                        }
                    }

                    //recieve
                    {
                        ssize_t n;
                        while ((n = coptr->conn.read(buf, sizeof(buf))) > 0) {
                            for (size_t i = 0; i < n; ++i)
                                msg.push(buf[i]);
                        }
                        if (!msg.empty() && !instance->shutdown) {
                            //parse all containing messages in the buffer
                            while (!msg.empty()) {
                                const char c = msg.front();
                                msg.pop();
                                //reached end of message
                                if (c == static_cast<char>(3)) {
                                    std::string message;
                                    message.reserve(curMsg.size());
                                    while (!curMsg.empty()) {
                                        message.push_back(curMsg.front());
                                        curMsg.pop();
                                    }
                                    logger->debug("Received: {}", message);
                                    cb(message);
                                } else
                                    curMsg.push(c);
                            }
                        }
                    }
                    //max 60 fps
                    const auto delta = 16ms - std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - now);
                    if (delta > 0ms) std::this_thread::sleep_for(delta);
                }
                
            });
        }

      
    };

}

#endif /* TCP_CLIENT_HPP */
