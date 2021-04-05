
#include "../../include/server/tcp_server.hpp"

net::TCP_Server* net::TCP_Server::instance = new net::TCP_Server();

net::TCP_Server::TCP_Server() noexcept {
    connections.resize(4);
    for(size_t i = 0; i < 4; ++i){
        shutdown.emplace_back(false);
        sendQueue.push_back(std::make_unique<util::BlockQueue<std::string>>());
    }
}

net::TCP_Server::~TCP_Server() noexcept{
    for(size_t i = 0; i < 4; ++i)
        shutdown[i]._a = true; 
}

void net::TCP_Server::disconect(Player _player) noexcept {
    const size_t id = static_cast<size_t>(_player) - 1;
    instance->shutdown[id]._a = true;
}

void net::TCP_Server::terminate() noexcept {
    auto logger = Logger::get("server_main");
    for(size_t i = 0; i < 4; ++i)
        instance->shutdown[i]._a = true; 
    instance->server_shutdown = true;
    logger->info("Shutdown recieved...");
}

void net::TCP_Server::barrier() noexcept {
    auto logger = Logger::get("server_main");
    logger->info("Waiting for shutdown...");
    char i;
    std::cin >> i;
    terminate();
    //while(!instance->shutdown)
        //std::this_thread::sleep_for(1s);
    logger->info("Waiting for threads to shut down...");

    instance->listener.wait_for(2s);
    for(auto& f : instance->connections){
        if(f.has_value())
            f.value().wait_for(2s);
    }

    logger->info("Goodbye!");
}

void net::TCP_Server::broadcast(const std::string& _msg){
    for(size_t i = 1; i < 5; ++i)
        sendToPlayer(static_cast<Player>(i), _msg);
}

void net::TCP_Server::sendToPlayer(Player _player, const std::string _msg){ 
    const size_t id = static_cast<size_t>(_player) - 1;
    if(!instance->connections[id].has_value())
        throw new ckException(_msg);
    instance->sendQueue[id]->push(_msg);
}