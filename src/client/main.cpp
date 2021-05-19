// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <nlohmann/json.hpp>
#include <sockpp/tcp_socket.h>
#include <wx/app.h>
#include "../../include/client/digital_UNO.hpp"
#include "../../include/client/player_controller.hpp"
#include "../../include/client/tcp_client.hpp"

// Macro which will generate a main function which serves as entry point into the program
wxIMPLEMENT_APP(digital_UNO);
/*
int main(){

	player_controller Player_Controller;

	Logger::init();

	try{
		auto port = 8081;
		net::TCP_Client::connect(port,[&](const std::string& _msg){Player_Controller.eval_response(_msg);});
	} catch(const ckException& _e){
        	auto logger = Logger::get("server_main");
        	logger->error("[exception] {}", _e.what());
        	return EXIT_FAILURE;
    	} catch(const std::exception& _e){
        	auto logger = Logger::get("server_main");
        	logger->error("[exception] {}", _e.what());
        	return EXIT_FAILURE;
    	}

		return 0;
	}


*/



