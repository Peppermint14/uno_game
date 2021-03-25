
#include "../../include/common/network.hpp"

net::TCP_Server* net::TCP_Server::instance = new net::TCP_Server();

net::TCP_Server::TCP_Server() noexcept {
    idsForPlayer.resize(4);
    callbacks.resize(4);
    for(size_t i = 0; i < 4; ++i)
        callbacks[i] = 0;
}

net::TCP_Server::~TCP_Server(){
    shutdown = true;
    listener.wait_for(2s);
    for(auto& f : connections){
        if(f.has_value())
            f.value().wait_for(2s);
    }
}

void net::TCP_Server::init(Logger _logger, uint32_t _port) {
    if(instance->isInit) throw new detail::TCPException("TCP_Server already initialised");
    instance->isInit = true;
    instance->logger = _logger;
    instance->listener = std::async(std::launch::async, [port = _port] {
        sockpp::tcp_acceptor acc(port);
        if (!acc) {
            std::stringstream str;
            str << "Error opening acceptor: " << acc.last_error_str();
            throw new detail::TCPException(str.str());
        }

        while (!instance->shutdown) {
            sockpp::tcp_socket sock = acc.accept();
            sock.read_timeout(0.25s);
            sock.write_timeout(0.25s);

            if (!sock) {
                spdlog::error("Error accepting incoming connection: {}", acc.last_error_str());
            } else {
                bool er = true;
                for (size_t i = 0; i < 4; ++i) {
                    if (instance->connections[i].has_value()) continue;
                    er = false;
                    instance->connections[i] = {std::async(std::launch::async, [id = i, instance = instance, sock = std::move(sock)]() mutable {
                        char buf[512];
                        using clock = std::chrono::high_resolution_clock;
                        while (instance->shutdown) {
                            auto now = clock::now();

                            //send
                            {
                                std::queue<std::string>& q = instance->sendQueue[id];
                                std::lock_guard<std::mutex> lock(instance->m_sendQueue[id]);
                                while (!q.empty()) {
                                    const std::string msg = q.front();
                                    sock.write(msg);
                                    q.pop();
                                }
                            }

                            //recieve
                            {
                                ssize_t n;
                                std::vector<char> msg;
                                while ((n = sock.read(buf, sizeof(buf))) > 0) {
                                    for (size_t i = 0; i < n; ++i) {
                                        msg.push_back(buf[i]);
                                    }
                                }
                                if (!msg.empty()) {
                                    std::string msg_st(msg.begin(), msg.end());
                                    std::lock_guard<std::mutex>(instance->m_callbacks[id]);
                                    if (instance->callbacks[id] != 0) {
                                        instance->callbacks[id](msg_st);
                                    }
                                }
                            }
                            //max 60 fps
                            auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - now);
                            std::this_thread::sleep_for(detail::MAX(0ms, delta));
                        }

                        sock.shutdown();
                    })};
                    sock.set_non_blocking(true);
                    nlohmann::json msg;
                    msg["id"] = 0;
                    msg["player"] = static_cast<uint32_t>(i);
                    TCP_Server::sendToPlayer(static_cast<detail::Player>(i), msg.dump());
                }
                if (er)
                    spdlog::error("cannot accept more connections");
            }
        }
    });
}

void net::TCP_Server::recieve(detail::Player _player, std::function<void(const std::string&)> _func){
    const size_t id = static_cast<size_t>(_player);
    std::lock_guard<std::mutex> lock(instance->m_callbacks[id]);
    instance->callbacks[id] = _func;
}

void net::TCP_Server::broadcast(const std::string& _msg){
    for(size_t i = 1; i < 5; ++i)
        sendToPlayer(static_cast<detail::Player>(i), _msg);
}

void net::TCP_Server::sendToPlayer(detail::Player _player, const std::string _msg){ 
    const size_t id = static_cast<size_t>(_player);
    if(!instance->connections[id].has_value())
        throw new detail::TCPException(_msg);
    std::lock_guard<std::mutex> lock(instance->m_sendQueue[id]);
    instance->sendQueue[id].push(_msg);
}