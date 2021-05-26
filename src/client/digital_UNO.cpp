// Copied from Lama example Project

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
    GameWindow* gameWindow = new GameWindow(
            "digital_UNO", // title of window,
            wxDefaultPosition, // position of the window
            wxDefaultSize // size of the window
    );
    gameWindow->Show(true);

    player_controller::init(gameWindow);

    return true;
}
