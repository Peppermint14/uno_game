#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "../common/common.hpp"

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_acceptor.h>

namespace net {

    class TCP_Client {

        std::queue<std::string> toSend;
        std::mutex mutex;
        std::optional<std::future<void>> connection;
        std::atomic<bool> shutdown = false;

        static TCP_Client* instance;

        TCP_Client() noexcept {}

    public:

        static void send(const std::string&) noexcept;
        static void terminate() noexcept;

        template<class T, class Func>
        static void connect(const std::string& _adress, T _port, Func _callback){
            static_assert(std::is_function(_callback));
            auto log = Logger::create("client_main");

            sockpp::tcp_connector conn;
            if (!conn.connect(sockpp::inet_address("localhost", port))){
                log->error("[Client] Error connecting: {}", conn.last_error_str());
                throw new ckException(conn.last_error_str());
            }

            instance->connection = { std::async(std::launch::async, [sock = std::move(conn), cb = _callback] mutable {

                char buf[512];
                using clock = std::chrono::high_resolution_clock;
                auto logger = Logger::create("client_connection");
                while (!instance->shutdown) {
                    auto now = clock::now();

                    //send
                    {
                        std::queue<std::string>& q = instance->toSend;
                        std::lock_guard<std::mutex> lock(instance->m_sendQueue[id]);
                        while (!q.empty()) {
                            const std::string msg = q.front();
                            sock.write(msg);
                            logger->debug("[Client] Sent: {}", msg);
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
                            logger->debug("[Client] Received: {}", msg_st);
                            cb(id, msg_st);
                        }
                    }
                    //max 60 fps
                    const auto delta = 16ms - std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - now);
                    if (delta > 0ms) std::this_thread::sleep_for(delta);
                }
                
            })};
        }

      
    };

}

#endif /* TCP_CLIENT_HPP */