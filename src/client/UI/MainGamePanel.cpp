// Copied from Lama example Project and heavily changed/adapted to our needs
#include <iostream>
#include "../../../include/client/UI/MainGamePanel.hpp"
#include "../../../include/client/UI/ImagePanel.hpp"
#include "../../../include/common/cards.hpp"
#include "../../../include/client/player_controller.hpp"
#include <wx/wx.h>
#include <wx/utils.h>
#include <wx/choicdlg.h>
#include <wx/msgdlg.h> 
#include <wx/textctrl.h>
// #include <wx/richtext/richtextctrl.h>


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
    
    wxString  res = wxGetSingleChoice(msg, caption, choices, this, 25, 25, true, 400, 200, 1);
    
    while(res.IsEmpty()) // Forces the player to maek a choice
        res = wxGetSingleChoice(msg, caption, choices);

    return res;
}

void MainGamePanel::buildPlayerState(Player_State* playerState, Player* me){

    // remove any existing UI
    this->DestroyChildren();
 

    // show both card piles at the center
    this->buildCardPiles(playerState);
    
    // show our own player
    this->buildThisPlayer(playerState, me);

    this->buildPlayerList(playerState);

    // Make player aware if the previous player has played his penultimate card
    if(playerState->get_uno()) this->show_uno_notification(playerState);

    // Make player aware if a wild card is played and he has to match a chosen colour
    if(playerState->get_to_be_matched() != ck_Cards::Color::NONE) this->show_colour_match_notification(playerState);

    // update layout
    this->Layout();

    // Make player aware if someone has won
    if(playerState->has_player_won()){
        if(playerState->get_winner() == playerState->get_this_player())
            this->show_won_notification(playerState);
        else 
            this->show_lost_notification(playerState);

        playerState->set_player_won(false);
    }

    if(playerState->get_game_over()){
        this->show_game_over_notification(playerState);
        playerState->set_game_over(0);
    }
}

//shows List of all players (playername(number of cards))
//and arrow indicating playdirection
void MainGamePanel::buildPlayerList(Player_State* playerState){
   if(!playerState->is_waiting_for_start()){ 
    	wxPoint pos = MainGamePanel::tableCenter + MainGamePanel::playerListOffset;
        
    	std::string header = "Players: name (#cards)\n\n";
    	std::string player = "";
    	std::string nof_cards = "";

    
    	wxTextCtrl* text = new wxTextCtrl(this, wxID_ANY, header, pos, playerListSize, wxBORDER_NONE|wxTE_MULTILINE|wxTE_NO_VSCROLL|wxTE_NOHIDESEL|wxTE_READONLY);
    	text->SetBackgroundColour(BG);
        wxFont font = *wxSWISS_FONT;
        font.SetSymbolicSize(wxFONTSIZE_LARGE);
        
        text->SetFont(font);
        
   

    	for(Player_id id : *(playerState->get_id_vec())){
		int n = playerState->get_number_of_cards(id);
        	if(n!=0){
			player = playerState->get_name_of_playerid(id) + " (" + std::to_string(n) + ")\n";
        		if(id == playerState->get_current_player()){
            			text->SetDefaultStyle(wxTextAttr(Higlight));
            			text->AppendText(player);
            			text->SetDefaultStyle(wxTextAttr(*wxBLACK, BG));
        		}
        		else text->AppendText(player);
		}	
    	}
    	text->SetSize(text->GetBestSize());
    
    // Play-Direction Indicator:
    
    	wxPoint posInd = pos + playDirectionOffset;
    	double arrow_direction = -1 + 2*playerState->get_play_direction(); // maps bool to -1 or 1
    	ImagePanel* DirectionIndicator = new ImagePanel(this, "../assets/arrow.png", wxBITMAP_TYPE_ANY, posInd, playDirectionSize, arrow_direction*twoPi/4);
   }    
}


void MainGamePanel::buildCardPiles(Player_State* playerState) {

    
    if(!playerState->is_waiting_for_start()) {

        // Show discard pile
        const ck_Cards::Cards* topCard = playerState->get_top_discard();
        if(topCard != nullptr) {
	    std::string cardImage;
	    if(uint32_t(*topCard)<100){
            	cardImage = "../assets/uno_cards/" + std::to_string(uint32_t(*topCard)) + ".png";
	    }
	    else{ //special treatment for color chosing cards
		ck_Cards::Color color = player_controller::get_color();
		cardImage = "../assets/uno_cards/" + std::to_string(uint32_t(*topCard))+"_"+std::to_string(uint32_t(color))+ ".png";
	    }

            wxPoint discardPilePosition = MainGamePanel::tableCenter + MainGamePanel::discardPileOffset;

            ImagePanel* discardPile = new ImagePanel(this, cardImage, wxBITMAP_TYPE_ANY, discardPilePosition, MainGamePanel::cardSize);
            discardPile->SetToolTip("Discard pile");
        }

        // Show draw pile
        wxPoint drawPilePosition = MainGamePanel::tableCenter + MainGamePanel::drawPileOffset;

        ImagePanel* drawPile = new ImagePanel(this, "../assets/uno_cards/back.png", wxBITMAP_TYPE_ANY, drawPilePosition, MainGamePanel::cardSize);

        if(playerState->get_players_turn() && !playerState->has_player_quit()) {
            drawPile->SetToolTip("Draw card");
            drawPile->SetCursor(wxCursor(wxCURSOR_HAND));
            drawPile->Bind(wxEVT_LEFT_UP, [](wxMouseEvent& event) {
                player_controller::drawCard();
            });
        } else {
            drawPile->SetToolTip("Draw pile");
        }

    } else {
        // if the game did not start yet, show a back side of a card in the center (only for the mood)
        wxPoint cardPosition = MainGamePanel::tableCenter - (MainGamePanel::cardSize / 2);
        new ImagePanel(this, "../assets/uno_cards/back.png", wxBITMAP_TYPE_ANY, cardPosition, MainGamePanel::cardSize);
    }
    

}

wxStaticText* MainGamePanel::buildTurnIndicator(Player_State *playerState) {

    	if (!playerState->get_players_turn()) {
           // if it's not our turn, display "waiting..."
            wxStaticText *playerStatus = buildStaticText(
                    "waiting for your turn...",
                    wxDefaultPosition,
                    wxSize(200, 32),
                    wxALIGN_CENTER
            );
	    return playerStatus;
        }
        else {
            // if it's not our turn, display "waiting..."
            wxStaticText *playerStatus = buildStaticText(
                    "It's you turn!",
                    wxDefaultPosition,
                    wxSize(200, 32),
                    wxALIGN_CENTER
            );
            return playerStatus;
	}    
}

//:::::::::::::::::::::::::::::::::::::
//waiting shows:
//	Playername, Button:StartGame
//playing shows:
//	Playername, HandOfMe, turnIndicator
//
//TODO: Exit BUTTON
//:::::::::::::::::::::::::::::::::::::
void MainGamePanel::buildThisPlayer(Player_State* playerState, Player* me){
    // Setup two nested box sizers, in order to align our player's UI to the bottom center
    wxBoxSizer* outerLayout = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(outerLayout);
    wxBoxSizer* innerLayout = new wxBoxSizer(wxVERTICAL);
    outerLayout->Add(innerLayout, 1, wxALIGN_BOTTOM);
    
    // Show the label with our player name
    wxStaticText* playerName = buildStaticText(
            //playerState->get_player_name(),
            me->get_player_name(),
            wxDefaultPosition,
            wxSize(200, 18),
            wxALIGN_CENTER,
            true
    );
    innerLayout->Add(playerName, 0, wxALIGN_CENTER);
    
    // if the game has not yet started we say so
    if(playerState->is_waiting_for_start()) {

        wxStaticText* playerPoints = buildStaticText(
                "Waiting for game to start...",
                wxDefaultPosition,
                wxSize(200, 18),
                wxALIGN_CENTER
        );
        innerLayout->Add(playerPoints, 0, wxALIGN_CENTER | wxBOTTOM, 8);

        // // show button that allows our player to start the game
        wxButton* startGameButton = new wxButton(this, wxID_ANY, "Start Game!", wxDefaultPosition, wxSize(160, 64));
        startGameButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) { player_controller::startGame();});

        innerLayout->Add(startGameButton, 0, wxALIGN_CENTER | wxBOTTOM, 8);

    } else{
	    //is it my turn or not
      	    wxStaticText *playerStatus = buildTurnIndicator(playerState);
            innerLayout->Add(playerStatus, 0, wxALIGN_CENTER | wxBOTTOM, 8);
        
        // if we haven't folded yet, and it's our turn, display Fold button
        //else if (!playerState->get_players_turn()) {
       	         
        wxButton *ExitButton = new wxButton(this, wxID_ANY, "EXIT/FOLD", wxDefaultPosition, wxSize(80, 32));
        ExitButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {
            wxExit();
        });
         innerLayout->Add(ExitButton, 0, wxALIGN_CENTER | wxBOTTOM, 8); 
		
        
        // display our player's hand, if we have cards
        int numberOfCards = playerState->get_number_of_cards(me->get_player_id());
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
                uint32_t number = uint32_t(i);
                std::string cardFile = "../assets/uno_cards/" + std::to_string(number) + ".png";

                ImagePanel *cardButton = new ImagePanel(this, cardFile, wxBITMAP_TYPE_ANY, wxDefaultPosition, scaledCardSize);
                if (playerState->get_players_turn() && !playerState->has_player_quit()) {
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


//is called by everyone when the player with id  has UNO
//TODO: this doesn't work like that -> should be a function one can call in the player_controller when receiving the UNO type from the server
void MainGamePanel::show_uno_notification(Player_State* ps){
    wxPoint popupPosition = MainGamePanel::tableCenter + MainGamePanel::unoPopupOffset;
    ImagePanel* uno_notification = new ImagePanel(this, "../assets/uno_popup.png", wxBITMAP_TYPE_ANY, popupPosition, MainGamePanel::popupSize);
    uno_notification->Show();
    ps->set_uno(false);
}

void MainGamePanel::show_won_notification(Player_State* ps){
    wxString message("Congratulations!\n");
    message += ps->get_player_name() + ", you have successfully beaten all your opponents.";
    wxMessageBox(message, "Winner", wxICON_NONE);
}
void MainGamePanel::show_lost_notification(Player_State* ps){
    wxString message("Unlucky...\n");
    message += ps->get_name_of_playerid(ps->get_winner()) + " has won the game.";
    wxMessageBox(message, "Lost", wxICON_NONE);
}

void MainGamePanel::show_game_over_notification(Player_State* ps){
    
    wxString message("The game is over. Everybody either won or lost.\nThe client will now close...");
    wxMessageDialog game_over(this, message, "Lost", wxOK|wxCANCEL|wxCENTRE);
    if(game_over.ShowModal())
        wxExit();

    
    
    /*
    wxString message("The game is over. Everybody either won or lost.\nIf you wish you can restart the game, if not the game will exit. Do you want to restart");
    wxMessageDialog game_over(this, message, "Lost", wxYES_NO|wxCANCEL|wxCENTRE);
    
    
    if(game_over.ShowModal() == wxID_YES){ // YES
        if(ps->get_winner() == ps->get_this_player())
            player_controller::startGame();
    }
    else{
        player_controller::exit();        
    }
    */
}

void MainGamePanel::show_colour_match_notification(Player_State* ps){

    wxString message("A wild card has been played! You have to match the following colour: \n");
    switch (uint32_t(ps->get_to_be_matched()))
    {
    case 0:
        message += "GREEN";
        break;

    case 1:
        message += "RED";
        break;

    case 2:
        message += "YELLOW";
        break;

    case 3:
        message += "BLUE";
        break;

    case 4:
        message += "ERROR";
        break;

    }
    wxMessageBox(message, "Match Colour", wxICON_INFORMATION);
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
