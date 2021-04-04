
#include "../../include/server/tcp_server.hpp"

net::TCP_Server* net::TCP_Server::instance = new net::TCP_Server();

net::TCP_Server::TCP_Server() noexcept {
    idsForPlayer.resize(4);
    callbacks.resize(4);
    for(size_t i = 0; i < 4; ++i)
        callbacks[i] = 0;
}

net::TCP_Server::~TCP_Server() noexcept{
    shutdown = true;  
}

void net::TCP_Server::terminate() noexcept {
    auto logger = Logger::get("server_main");
    instance->shutdown = true;
    logger->info("Shutdown recieved...");
}

void net::TCP_Server::barrier() noexcept {
    auto logger = Logger::get("server_main");
    logger->info("Waiting for shutdown...");
    while(!instance->shutdown)
        std::this_thread::sleep_for(1s);
    logger->info("Waiting for threads to shut down...");

    instance->listener.wait_for(2s);
    for(auto& f : instance->connections){
        if(f.has_value())
            f.value().wait_for(2s);
    }

    logger->info("Goodbye!");
}

void net::TCP_Server::recieve(Player _player, std::function<void(const std::string&)> _func){
    const size_t id = static_cast<size_t>(_player);
    std::lock_guard<std::mutex> lock(instance->m_callbacks[id]);
    instance->callbacks[id] = _func;
}

void net::TCP_Server::broadcast(const std::string& _msg){
    for(size_t i = 1; i < 5; ++i)
        sendToPlayer(static_cast<Player>(i), _msg);
}

void net::TCP_Server::sendToPlayer(Player _player, const std::string _msg){ 
    const size_t id = static_cast<size_t>(_player);
    if(!instance->connections[id].has_value())
        throw new ckException(_msg);
    std::lock_guard<std::mutex> lock(instance->m_sendQueue[id]);
    instance->sendQueue[id].push(_msg);
}