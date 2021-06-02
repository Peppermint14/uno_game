
#include "../../include/common/common.hpp"
#include "../../include/client/tcp_client.hpp"

int main() {

    Logger::init();

    try {
        net::TCP_Client::connect("46.14.54.6", 8080, [](const std::string& _msg){
            auto log = Logger::get("client_main");
            log->debug("[cb] {}", _msg);
        });
    } catch(const ckException& _e){
        auto logger = Logger::get("client_main");
        logger->error("[exception] {}", _e.what());
        return EXIT_FAILURE;
    } catch(const std::exception& _e){
        auto logger = Logger::get("client_main");
        logger->error("[exception] {}", _e.what());
        return EXIT_FAILURE;
    }

    for(size_t i = 0; i < 10; ++i)
        net::TCP_Client::send("bingbong");

    net::TCP_Client::barrier();

    std::cout << "ding" << std::endl;

    return EXIT_SUCCESS;
}
