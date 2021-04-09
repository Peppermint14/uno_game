// Copied from Lama example Project

#include "../../include/client/digital_UNO.hpp"
#include "../../include/client/UI/MainGamePanel.hpp"
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
    player_controller::init(gameWindow);

    // Initializing shit here could be moved to player_controller (like they do in the lama project)
    
    // ConnectionPanel* CP = new ConnectionPanel(gameWindow);
    // MainGamePanel* MGP = new MainGamePanel(gameWindow);

    // CP->Show(false);
    // MGP->Show(false);
    // gameWindow->showPanel(CP);

    return true;
}
