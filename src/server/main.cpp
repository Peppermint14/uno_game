
#include "../../include/common/common.hpp"
#include "../../include/server/tcp_server.hpp"
#include "../../include/server/game_controller.hpp"

int main() {

    Game_Controller game_controller;
    
    Logger::init();

    try{ 
    net::TCP_Server::init(8080, [&](Player_id _player, const std::string& _msg){
        //auto logger = Logger::get("server_main");
        //logger->info("[callback][{}] {}", static_cast<size_t>(_player), _msg);
        game_controller.eval_request(_player, _msg);
        //net::TCP_Server::sendToPlayer(_player, _msg);
    });
    	//server_network_manager server;

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
