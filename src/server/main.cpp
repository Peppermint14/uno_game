
#include "../../include/common/common.hpp"
#include "../../include/server/tcp_server.hpp"

int main() {

    Logger::init();

    try{ 
        net::TCP_Server::init(8080, [](Player _player, const std::string& _msg){
            //GameController::eval(_player, _msg);
        });
    } catch(const ckException& _e){
        auto logger = Logger::get("server_main");
        logger->error("[exception] {}", _e.what());
        return EXIT_FAILURE;
    } catch(const std::exception& _e){
        auto logger = Logger::get("server_main");
        logger->error("[exception] {}", _e.what());
        return EXIT_FAILURE;
    }

    net::TCP_Server::barrier();

    return EXIT_SUCCESS;
}