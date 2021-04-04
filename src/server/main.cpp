
#include "../../include/common/common.hpp"
#include "../../include/server/tcp_server.hpp"

int main() {

    Logger::init();

    try{ 
    net::TCP_Server::init(80, [](Player _player, const std::string& _msg){
        auto logger = Logger::get("server_main");
        logger->error("[{}] {}", static_cast<size_t>(_player), _msg);
    });
    } catch(const ckException& _e){
        auto logger = Logger::get("server_main");
        logger->error(_e.what());
        return EXIT_FAILURE;
    };

    net::TCP_Server::barrier();

    return EXIT_SUCCESS;
}