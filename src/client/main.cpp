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

	player_controller* Player_Controller = new player_controller();

	//Logger::init();
	
	try{
		//auto port = 8081;
		//net::TCP_Client::connect(port,[&](const std::string& _msg){Player_Controller.eval_response(_msg);});
		// Allow loading of JPEG  and PNG image files
    		wxImage::AddHandler(new wxJPEGHandler());
    		wxImage::AddHandler(new wxPNGHandler());

    // Open main game window
    		GameWindow* gameWindow = new GameWindow(
            		"digital_UNO", // title of window,
            		wxDefaultPosition, // position of the window
            		wxDefaultSize // size of the window
    		);
    		gameWindow->Show(true);

    		// Initialize player controller

    		//Player_Controller = new player_controller();
    		Player_Controller->init(gameWindow);


	} catch(const ckException& _e){
        	auto logger = Logger::get("server_main");
        	logger->error("[exception] {}", _e.what());
        	return EXIT_FAILURE;
	}
    
		return 0;
	}


*/



