
#include "../../include/client/tcp_client.hpp"

net::TCP_Client* net::TCP_Client::instance = new net::TCP_Client();


// net::TCP_Client::TCP_Client() noexcept {
// 	toSend = std::make_unique<util::BlockQueue<std::string>>();   
// 	shutdown = false;
// }
/*
net::TCP_Client::~TCP_Client() noexcept{
        shutdown = true; 
}*/


void net::TCP_Client::send(const std::string& _msg) noexcept {
    std::lock_guard<std::mutex> lock(instance->mutex);
    instance->toSend->push(_msg);
}

void net::TCP_Client::terminate() noexcept {
    auto log = Logger::get("client_main");
    log->info("Shutdown recieved.");
    instance->shutdown = true;
}

//use for debug and test purpose only
void net::TCP_Client::barrier() noexcept {
    auto logger = Logger::get("client_main");
    logger->info("Waiting for shutdown...");
    char i;
    std::cin >> i;
    terminate();
    logger->info("Waiting for threads to shut down...");

    logger->info("Goodbye!");
}


//from other



