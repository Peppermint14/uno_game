// Copied from Lama example Project

#include "../../../include/client/UI/ConnectionPanel.hpp"
#include "../../../include/client/UI/ImagePanel.hpp"
#include "../../../include/client/player_controller.hpp"

//#include "../../common/network/default.conf"

const std::string default_server_host = "127.0.0.1";
const unsigned int default_port = 8080;



ConnectionPanel::ConnectionPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    
    //delete
    connectButtonclicked = false;

    wxColor white = wxColor(255, 255, 255);
    this->SetBackgroundColour(white);

    wxBoxSizer* verticalLayout = new wxBoxSizer(wxVERTICAL);

    ImagePanel* logo = new ImagePanel(this, "../assets/uno_logo.png", wxBITMAP_TYPE_ANY, wxDefaultPosition, wxSize(200, 250));
    verticalLayout->Add(logo, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 10);

    this->_serverAddressField = new InputField(
        this, // parent element
        "Server address:", // label
        100, // width of label
        /*"46.14.54.6",*/ // default value (variable from "default.conf")
	"127.0.0.1",
        240 // width of field
    );
    verticalLayout->Add(this->_serverAddressField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    this->_serverPortField = new InputField(
        this, // parent element
        "Server port:", // label
        100, // width of label
        wxString::Format("%i", default_port), // default value (variable from "default.conf")
        240 // width of field
    );
    verticalLayout->Add(this->_serverPortField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

    this->_playerNameField = new InputField(
        this, // parent element
        "Player name:", // label
        100, // width of label
        "name", // default value
        240 // width of field
    );
    verticalLayout->Add(this->_playerNameField, 0, wxTOP | wxLEFT | wxRIGHT, 10);
    //delete
   // connectButton = new wxButton(this, wxID_ANY, "Connect", wxDefaultPosition, wxSize(100, 40));
    wxButton* connectButton = new wxButton(this, wxID_ANY, "Connect", wxDefaultPosition, wxSize(100, 40));
    //connectButton->Bind(wxEVT_BUTTON, &ConnectionPanel::buttonClicked(&event), this);
    //connectButton->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {player_controller::connectToServer();});
    // connectButton->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {buttonClicked();});
    connectButton->Bind(wxEVT_BUTTON, [](wxCommandEvent& event) {player_controller::connectToServer();});
    
    verticalLayout->Add(connectButton, 0, wxALIGN_RIGHT | wxALL, 10);

    this->SetSizerAndFit(verticalLayout);
}


wxString ConnectionPanel::getServerAddress() {
    return this->_serverAddressField->getValue();
}


wxString ConnectionPanel::getServerPort() {
    return this->_serverPortField->getValue();
}


wxString ConnectionPanel::getPlayerName() {
    return this->_playerNameField->getValue();
}


// TODO: On button click proceed to mainPanel and other stuff
//void ConnectionPanel::buttonClicked(wxCommandEvent &event){
    
void ConnectionPanel::buttonClicked(){
    connectButtonclicked = true;
    return;
}
