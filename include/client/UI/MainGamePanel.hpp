// Copied from Lama example Project and slightly adapted.

#ifndef DIGITALUNO_CLIENT_MAINGAMEPANEL_HPP
#define DIGITALUNO_CLIENT_MAINGAMEPANEL_HPP

#include <wx/wx.h>
#include "../player_state.hpp"
#include "../player.hpp"
#include "ImagePanel.hpp"


class MainGamePanel : public wxPanel {

public:
    MainGamePanel(wxWindow* parent);
    void buildPlayerState(Player_State* playerState, Player* me);
    wxString colourPicker();
    // Notification alerts
    void show_colour_match_notification();
    void show_uno_notification(Player_State*);

private:

    void buildThisPlayer(Player_State* playerState, Player* me);
    void buildCardPiles(Player_State* playerState);
    void buildPlayerList(Player_State* playerState);
    void buildPlayDirectionIndicator(Player_State* playerState);
    

    wxStaticText* buildTurnIndicator(Player_State* playerState);
    // Notification alerts
    void show_colour_match_notification(Player_State*);
    void show_won_notification(Player_State*);
    void show_lost_notification(Player_State*);

    
    void show_game_over_notification(Player_State*);

    wxStaticText* buildStaticText(std::string content, wxPoint position, wxSize size, long textAlignment, bool bold = false);

    wxSize getBoundsOfRotatedSquare(double edgeLength, double rotationAngle);
    double getEdgeLengthOfRotatedSquare(double originalEdgeLength, double rotationAngle);

    wxPoint getPointOnEllipse(double horizontalRadius, double verticalRadius, double angle);

    // define key constant layout values
    wxSize const panelSize = wxSize(960, 680); // also set in the constructor implementation
    wxPoint const tableCenter = wxPoint(480, 300);
    wxSize const cardSize = wxSize(80, 124);
    // size of popup window (Uno)
    wxSize const popupSize = wxSize(225, 140);
    // size of the player list
    wxSize const playerListSize = wxSize(200,102);
    wxSize const playDirectionSize = wxSize(40, 75); // size of the play direction arrow
    

    wxColour BG = wxColour(200,210,100); // Same colour as normal background
    wxColour Higlight = wxColour(204,0,34); // Colour of highlighted player


    double const otherPlayerHandSize = 160.0;
    double const otherPlayerHandDistanceFromCenter = 180.0;
    double const otherPlayerLabelDistanceFromCenter = 275.0;

    wxPoint const discardPileOffset = wxPoint(-84, -42);
    wxPoint const drawPileOffset = wxPoint(4, -42);
    wxPoint const turnIndicatorOffset = wxPoint(-100, 98);


    wxPoint const playerListOffset = wxPoint(130, -260);
    wxPoint const playDirectionOffset = wxPoint(-65, 20);
    wxPoint const unoPopupOffset = wxPoint(-185, -250);

    double const twoPi = 6.28318530718;

};


#endif //DIGITALUNO_CLIENT_MAINGAMEPANEL_HPP
