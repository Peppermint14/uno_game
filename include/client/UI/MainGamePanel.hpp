// Copied from Lama example Project

#ifndef DIGITALUNO_CLIENT_MAINGAMEPANEL_HPP
#define DIGITALUNO_CLIENT_MAINGAMEPANEL_HPP

#include <wx/wx.h>
#include "../player_state.hpp"
#include "../player.hpp"


class MainGamePanel : public wxPanel {

public:
    MainGamePanel(wxWindow* parent);

    void buildPlayerState(Player_State* playerState, Player* me);
    wxString colourPicker();


private:

    
    void buildThisPlayer(Player_State* playerState, Player* me);
    void buildCardPiles(Player_State* playerState, Player *me);
    void buildPlayerList(Player_State* playerState, Player* me);
    void buildPlayDirectionIndicator(Player_State* playerState);


    void buildOtherPlayerHand(Player_State* playerState, Player* otherPlayer, double playerAngle);
    void buildOtherPlayerLabels(Player_State* playerState, Player* otherPlayer, double playerAngle, int side);
    void buildTurnIndicator(Player_State* playerState, Player* me);

    wxStaticText* buildStaticText(std::string content, wxPoint position, wxSize size, long textAlignment, bool bold = false);

    wxSize getBoundsOfRotatedSquare(double edgeLength, double rotationAngle);
    double getEdgeLengthOfRotatedSquare(double originalEdgeLength, double rotationAngle);

    wxPoint getPointOnEllipse(double horizontalRadius, double verticalRadius, double angle);

    // define key constant layout values
    wxSize const panelSize = wxSize(960, 680); // also set in the constructor implementation
    wxPoint const tableCenter = wxPoint(480, 300);
    wxSize const cardSize = wxSize(80, 124);

    double const otherPlayerHandSize = 160.0;
    double const otherPlayerHandDistanceFromCenter = 180.0;
    double const otherPlayerLabelDistanceFromCenter = 275.0;

    wxPoint const discardPileOffset = wxPoint(-84, -42);
    wxPoint const drawPileOffset = wxPoint(4, -42);
    wxPoint const turnIndicatorOffset = wxPoint(-100, 98);

    double const twoPi = 6.28318530718;

};


#endif //DIGITALUNO_CLIENT_MAINGAMEPANEL_HPP
