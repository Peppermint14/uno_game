
#include "../../include/client/tcp_client.hpp"

net::TCP_Client* net::TCP_Client::instance = new net::TCP_Client();

net::TCP_Server::TCP_Server() noexcept {
    shutdown = false;
    sendQueue = std::make_unique<util::BlockQueue<std::string>>();
    /*connections.resize(4);
    for(size_t i = 0; i < 4; ++i){
        shutdown.emplace_back(false);
        sendQueue.push_back(std::make_unique<util::BlockQueue<std::string>>());
    }*/
}

net::TCP_Server::~TCP_Server() noexcept{
        shutdown._a = true; 
}

void net::TCP_Server::disconect() noexcept {
    instance->shutdown._a = true;
}

void net::TCP_Server::terminate() noexcept {
    auto logger = Logger::get("client_main");  
    instance->client_shutdown = true;
    logger->info("Shutdown recieved...");
}

void net::TCP_Server::barrier() noexcept {
    using clock = std::chrono::high_resolution_clock;
    auto logger = Logger::get("client_main");
    logger->info("Waiting for shutdown...");

    auto f = std::async(std::launch::async, []{
        while(true) {
            std::string in;
            std::cin >> in;
            if(in == "q")
                return in;
        }
        return std::string("q");
    });

    while(!f.valid() && !instance->client_shutdown){
        auto now = clock::now();

        while(!instance->cbQueue.empty()){
            const auto v = instance->cbQueue.front();
            instance->cbQueue.pop();
            instance->cb(std::get<0>(v), std::get<1>(v));
        }
        //max 60 fps
        const auto delta = 16ms - std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - now);
        if(delta > 0ms) std::this_thread::sleep_for(delta);
    }
    instance->shutdown._a = true; 

    logger->info("Waiting for threads to shut down...");

    instance->listener.wait_for(2s);
        if(instance->connection.has_value())
            instance->connection.value().wait_for(2s);

    logger->info("Goodbye!");
}


void net::TCP_Client::send(const std::string _msg){ 
    const size_t id = static_cast<size_t>(_player) - 1;
    if(!instance->connection.has_value())
        throw new ckException(_msg);
    instance->sendQueue->push(_msg);
}
