#include "../../include/client/digital_UNO.hpp"
#include "../../include/client/player_controller.hpp"
#include "../../include/client/UI/GameWindow.hpp"

// Application entry point
bool digital_UNO::OnInit()
{
    Logger::init();
    // Allow loading of JPEG  and PNG image files
    wxImage::AddHandler(new wxJPEGHandler());
    wxImage::AddHandler(new wxPNGHandler());

    // Open main game window
    //GameWindow* gameWindow = new GameWindow(
    GameWindow* gameWindow = new GameWindow(
            "digital_UNO", // title of window,
            wxDefaultPosition, // position of the window
            wxDefaultSize // size of the window
    );
    gameWindow->Show(true);

    // Initialize player controller
    player_controller::init(gameWindow);

    return true;
}

int digital_UNO::OnExit(){
    player_controller::exit();
    net::TCP_Client::terminate();
    return 0;
}
