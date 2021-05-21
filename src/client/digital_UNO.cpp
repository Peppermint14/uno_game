// Copied from Lama example Project

#include "../../include/client/digital_UNO.hpp"
#include "../../include/client/player_controller.hpp"


// Application entry point
bool digital_UNO::OnInit()
{
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

    controller = new player_controller();
    controller->init(gameWindow);
    //player_controller* _player_controller;
    //_player_controller->init(gameWindow);
    //player_controller::init(gameWindow);
    //_player_controller = new player_controller(); 
    //_player_controller->init(gameWindow);

    return true;
}

int digital_UNO::OnExit(){
    delete controller;
    return 0;
}
