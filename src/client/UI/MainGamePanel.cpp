// Copied from Lama example Project
#include <iostream>
#include "../../../include/client/UI/MainGamePanel.hpp"
#include "../../../include/client/UI/ImagePanel.hpp"
#include "../../../include/common/cards.hpp"
#include "../../../include/client/player_controller.hpp"
// #include <wx/aboutdlg.h> 
// #include <wx/colordlg.h> 
// #include <wx/propdlg.h>
#include <wx/choicdlg.h> 


MainGamePanel::MainGamePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(960, 680)) {
}

wxString MainGamePanel::colourPicker(){
    
    // TODO: Adjust size of Window
    wxArrayString choices;
    choices.Add("Red");
    choices.Add("Green");
    choices.Add("Blue");
    choices.Add("Yellow");
    wxString msg("Choose the colour");
    wxString caption("Wildcard");

    //int x,y,width,height,initialSelection;
    //bool centre;

    // wxSize size(400, 500);

    // wxDialog dialog(NULL, -1, "test", wxDefaultPosition, size);
    
    // dialog.Show();

    wxString  res = wxGetSingleChoice(msg, caption, choices, this, 25, 25, true, 400, 200, 1);
    
    while(res.IsEmpty())
        res = wxGetSingleChoice(msg, caption, choices);
    // test.SetSelection(initialSelection);
    // return test.ShowModal() == wxID_OK ? test.GetStringSelection() : wxString();

    return res;
}

void MainGamePanel::buildPlayerState(Player_State* playerState, Player* me) {

    // remove any existing UI
    this->DestroyChildren();

    /*
    std::vector<player*> players = playerState->get_players();
    int numberOfPlayers = players.size();

    // find our own player object in the list of players
    int myPosition = -1;
    std::vector<player*>::iterator it = std::find_if(players.begin(), players.end(), [me](const player* x) {
        return x->get_id() == me->get_id();
    });
    if (it < players.end()) {
        me = *it;
        myPosition = it - players.begin();
    } else {
        GameController::showError("Game state error", "Could not find this player among players of server game.");
        return;
    }

    double anglePerPlayer = MainGamePanel::twoPi / (double) numberOfPlayers;

    // show all other players
    for(int i = 1; i < numberOfPlayers; i++) {

        // get player at i-th position after myself
        player* otherPlayer = players.at((myPosition + i) % numberOfPlayers);

        double playerAngle = (double) i * anglePerPlayer;
        int side = (2 * i) - numberOfPlayers; // side < 0 => right, side == 0 => center, side > 0 => left

        this->buildOtherPlayerHand(playerState, otherPlayer, playerAngle);
        this->buildOtherPlayerLabels(playerState, otherPlayer, playerAngle, side);
    }

    // show both card piles at the center
    this->buildCardPiles(playerState, me);

    // show turn indicator below card piles
    this->buildTurnIndicator(playerState, me);
    */
    // show our own player
    this->buildThisPlayer(playerState, me);

    // update layout
    this->Layout();
    
}


void MainGamePanel::buildOtherPlayerHand(Player_State* playerState, Player* otherPlayer, double playerAngle) {


    
    /*
    // define the ellipse which represents the virtual player circle
    double horizontalRadius = MainGamePanel::otherPlayerHandDistanceFromCenter * 1.4; // 1.4 to horizontally elongate players' circle
    double verticalRadius = MainGamePanel::otherPlayerHandDistanceFromCenter;

    // get this player's position on that ellipse
    wxPoint handPosition = MainGamePanel::tableCenter;
    handPosition += this->getPointOnEllipse(horizontalRadius, verticalRadius, playerAngle);

    // add image of player's hand
    int numberOfCards = otherPlayer->get_nof_cards();
    if(numberOfCards > 0) {

        // get new bounds of image, as they increase when image is rotated
        wxSize boundsOfRotatedHand = this->getBoundsOfRotatedSquare(MainGamePanel::otherPlayerHandSize, playerAngle);
        handPosition -= boundsOfRotatedHand / 2;

        std::string handImage = "assets/lama_hand_" + std::to_string(numberOfCards) + ".png";
        if(numberOfCards > 10) {
            handImage = "assets/lama_hand_10.png";
        }
        new ImagePanel(this, handImage, wxBITMAP_TYPE_ANY, handPosition, boundsOfRotatedHand, playerAngle);

    } else if(numberOfCards == 0) {

        wxSize nonRotatedSize = wxSize((int) MainGamePanel::otherPlayerHandSize, (int) MainGamePanel::otherPlayerHandSize);
        handPosition -= nonRotatedSize / 2;

        new ImagePanel(this, "assets/lama_hand_0.png", wxBITMAP_TYPE_ANY, handPosition, nonRotatedSize);
    }
    */
}


void MainGamePanel::buildOtherPlayerLabels(Player_State* playerState, Player* otherPlayer, double playerAngle, int side) {

    /*
    long textAlignment = wxALIGN_CENTER;
    int labelOffsetX = 0;

    if(side < 0) { // right side
        textAlignment = wxALIGN_LEFT;
        labelOffsetX = 85;

    } else if(side > 0) { // left side
        textAlignment = wxALIGN_RIGHT;
        labelOffsetX = -85;
    }

    // define the ellipse which represents the virtual player circle
    double horizontalRadius = MainGamePanel::otherPlayerLabelDistanceFromCenter * 1.25; // 1.25 to horizontally elongate players' circle (but less than the hands' circle)
    double verticalRadius = MainGamePanel::otherPlayerLabelDistanceFromCenter;

    // get this player's position on that ellipse
    wxPoint labelPosition = MainGamePanel::tableCenter;
    labelPosition += this->getPointOnEllipse(horizontalRadius, verticalRadius, playerAngle);
    labelPosition += wxSize(labelOffsetX, 0);

    // if game has not yet started, we only have two lines
    if(!playerState->is_started()) {
        this->buildStaticText(
                otherPlayer->get_player_name(),
                labelPosition + wxSize(-100, -18),
                wxSize(200, 18),
                textAlignment,
                true
        );
        this->buildStaticText(
                "waiting...",
                labelPosition + wxSize(-100, 0),
                wxSize(200, 18),
                textAlignment
        );

    } else {
        this->buildStaticText(
                otherPlayer->get_player_name(),
                labelPosition + wxSize(-100, -27),
                wxSize(200, 18),
                textAlignment,
                true
        );
        this->buildStaticText(
                std::to_string(otherPlayer->get_score()) + " minus points",
                labelPosition + wxSize(-100, -9),
                wxSize(200, 18),
                textAlignment
        );

        // Show other player's status label
        std::string statusText = "waiting...";
        bool bold = false;
        if(otherPlayer->has_folded()) {
            statusText = "Folded!";
        } else if(otherPlayer == playerState->get_current_player()) {
            statusText = "their turn";
            bold = true;
        }
        this->buildStaticText(
                statusText,
                labelPosition + wxSize(-100, 9),
                wxSize(200, 18),
                textAlignment,
                bold
        );
    }
    */
}


void MainGamePanel::buildCardPiles(Player_State* playerState, Player *me) {

    /*
    if(playerState->is_waiting()) {

        // Show discard pile
        const card* topCard = playerState->get_discard_pile()->get_top_card();
        if(topCard != nullptr) {
            std::string cardImage = "assets/lama_" + std::to_string(topCard->get_value()) + ".png";

            wxPoint discardPilePosition = MainGamePanel::tableCenter + MainGamePanel::discardPileOffset;

            ImagePanel* discardPile = new ImagePanel(this, cardImage, wxBITMAP_TYPE_ANY, discardPilePosition, MainGamePanel::cardSize);
            discardPile->SetToolTip("Discard pile");
        }

        // Show draw pile
        wxPoint drawPilePosition = MainGamePanel::tableCenter + MainGamePanel::drawPileOffset;

        ImagePanel* drawPile = new ImagePanel(this, "assets/lama_back.png", wxBITMAP_TYPE_ANY, drawPilePosition, MainGamePanel::cardSize);

        if(playerState->get_current_player() == me && !me->has_folded()) {
            drawPile->SetToolTip("Draw card");
            drawPile->SetCursor(wxCursor(wxCURSOR_HAND));
            drawPile->Bind(wxEVT_LEFT_UP, [](wxMouseEvent& event) {
                GameController::drawCard();
            });
        } else {
            drawPile->SetToolTip("Draw pile");
        }

    } else {
        // if the game did not start yet, show a back side of a card in the center (only for the mood)
        wxPoint cardPosition = MainGamePanel::tableCenter - (MainGamePanel::cardSize / 2);
        new ImagePanel(this, "assets/lama_back.png", wxBITMAP_TYPE_ANY, cardPosition, MainGamePanel::cardSize);
    }
    */

}

void MainGamePanel::buildTurnIndicator(Player_State *playerState, Player *me) {

    /*
    if(playerState->is_started() && playerState->get_current_player() != nullptr) {

        std::string turnIndicatorText = "It's " + playerState->get_current_player()->get_player_name() + "'s turn!";
        if(playerState->get_current_player() == me) {
            turnIndicatorText = "It's your turn!";
        }

        wxPoint turnIndicatorPosition = MainGamePanel::tableCenter + MainGamePanel::turnIndicatorOffset;

        this->buildStaticText(
                turnIndicatorText,
                turnIndicatorPosition,
                wxSize(200, 18),
                wxALIGN_CENTER,
                true
        );
    }
    */
}


void MainGamePanel::buildThisPlayer(Player_State* playerState, Player* me) {


    

    // Setup two nested box sizers, in order to align our player's UI to the bottom center
    wxBoxSizer* outerLayout = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(outerLayout);
    wxBoxSizer* innerLayout = new wxBoxSizer(wxVERTICAL);
    outerLayout->Add(innerLayout, 1, wxALIGN_BOTTOM);
    
    // Show the label with our player name
    std::string name = "MEEEE";
    wxStaticText* playerName = buildStaticText(
            name,
            //me->get_player_name(),
            wxDefaultPosition,
            wxSize(200, 18),
            wxALIGN_CENTER,
            true
    );
    innerLayout->Add(playerName, 0, wxALIGN_CENTER);

    // if the game has not yet started we say so
    if(playerState->is_waiting()) {

        wxStaticText* playerPoints = buildStaticText(
                "waiting for game to start...",
                wxDefaultPosition,
                wxSize(200, 18),
                wxALIGN_CENTER
        );
        innerLayout->Add(playerPoints, 0, wxALIGN_CENTER | wxBOTTOM, 8);

        // // show button that allows our player to start the game
        // wxButton* startGameButton = new wxButton(this, wxID_ANY, "Start Game!", wxDefaultPosition, wxSize(160, 64));
        // startGameButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        //     GameController::startGame();
        // });
        // innerLayout->Add(startGameButton, 0, wxALIGN_CENTER | wxBOTTOM, 8);

    } else {

        /*
        // show our player's minus points
        /*wxStaticText *playerPoints = buildStaticText(
                std::to_string(me->get_score()) + " minus points",
                wxDefaultPosition,
                wxSize(200, 18),
                wxALIGN_CENTER
        );
        innerLayout->Add(playerPoints, 0, wxALIGN_CENTER | wxBOTTOM, 8);
        */


        // if our player folded, we display that as status
        if (playerState->has_player_won()) {
            wxStaticText *playerStatus = buildStaticText(
                    "WON!",
                    wxDefaultPosition,
                    wxSize(200, 32),
                    wxALIGN_CENTER
            );
            innerLayout->Add(playerStatus, 0, wxALIGN_CENTER | wxBOTTOM, 8);

        }
        // if we haven't folded yet, and it's our turn, display Fold button
        // else if (playerState->get_current_player() == me) {
        //     wxButton *ExitButton = new wxButton(this, wxID_ANY, "Fold", wxDefaultPosition, wxSize(80, 32));
        //     foldButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
        //         Player::fold();
        //     });
        //     innerLayout->Add(foldButton, 0, wxALIGN_CENTER | wxBOTTOM, 8);

        // }// if it's not our turn, display "waiting..."
        else {
            wxStaticText *playerStatus = buildStaticText(
                    "waiting for your turn...",
                    wxDefaultPosition,
                    wxSize(200, 32),
                    wxALIGN_CENTER
            );
            innerLayout->Add(playerStatus, 0, wxALIGN_CENTER | wxBOTTOM, 8);
        }
        
        // display our player's hand, if we have cards
        int numberOfCards = playerState->get_nof_cards();
        if (numberOfCards > 0) {

            // create horizontal layout for the individual hand cards of our player
            wxBoxSizer *handLayout = new wxBoxSizer(wxHORIZONTAL);
            innerLayout->Add(handLayout, 0, wxALIGN_CENTER);

            wxSize scaledCardSize = MainGamePanel::cardSize;

            // Adjust card size (if the number of cards does not fit on the screen)
            if (numberOfCards * (MainGamePanel::cardSize.GetWidth() + 8) >
                MainGamePanel::panelSize.GetWidth()) { // 8 -> 4 pixel padding on both sides
                int scaledCardWidth = (MainGamePanel::panelSize.GetWidth() / numberOfCards) - 8;
                double cardAspectRatio =
                        (double) MainGamePanel::cardSize.GetHeight() / (double) MainGamePanel::cardSize.GetWidth();
                int scaledCardHeight = (int) ((double) scaledCardWidth * cardAspectRatio);
                scaledCardSize = wxSize(scaledCardWidth, scaledCardHeight);
            }

            // Show all cards
            ck_Cards::Hand *hand = playerState->get_hand();
            std::list<ck_Cards::Cards>  cards = hand->get_cards();
            for ( auto i : cards) {
                u_int32_t number = u_int32_t(i);
                std::string cardFile = "../assets/uno_cards/" + std::to_string(number) + ".png";

                ImagePanel *cardButton = new ImagePanel(this, cardFile, wxBITMAP_TYPE_ANY, wxDefaultPosition, scaledCardSize);

                if (playerState->get_players_turn()) {
                    cardButton->SetToolTip("Play card");
                    cardButton->SetCursor(wxCursor(wxCURSOR_HAND));
                    cardButton->Bind(wxEVT_LEFT_UP, [i](wxMouseEvent& event) {
                        player_controller::playCard(&i);
                    });
                }
                handLayout->Add(cardButton, 0, wxLEFT | wxRIGHT, 4);
            }
        }
    }    
}


wxStaticText* MainGamePanel::buildStaticText(std::string content, wxPoint position, wxSize size, long textAlignment, bool bold) {
    wxStaticText* staticText = new wxStaticText(this, wxID_ANY, content, position, size, textAlignment);
    if(bold) {
        wxFont font = staticText->GetFont();
        font.SetWeight(wxFONTWEIGHT_BOLD);
        staticText->SetFont(font);
    }
    return staticText;
}


wxSize MainGamePanel::getBoundsOfRotatedSquare(double edgeLength, double rotationAngle) {
    double newEdgeLength = this->getEdgeLengthOfRotatedSquare(edgeLength, rotationAngle);
    return wxSize(newEdgeLength, newEdgeLength);
}


double MainGamePanel::getEdgeLengthOfRotatedSquare(double originalEdgeLength, double rotationAngle) {
    return originalEdgeLength * (abs(sin(rotationAngle)) + abs(cos(rotationAngle)));
}


wxPoint MainGamePanel::getPointOnEllipse(double horizontalRadius, double verticalRadius, double angle) {
    return wxPoint((int) (sin(angle) * horizontalRadius), (int) (cos(angle) * verticalRadius));
}
