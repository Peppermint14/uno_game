// Copied from Lama example Project

#ifndef CONNECTIONPANEL_H
#define CONNECTIONPANEL_H

#include <wx/wx.h>
#include "InputField.hpp"

class ConnectionPanel : public wxPanel {

public:
    ConnectionPanel(wxWindow* parent);

    wxString getServerAddress();
    wxString getServerPort();
    wxString getPlayerName();
    void buttonClicked();
    bool connectButtonclicked;
private:
    InputField* _serverAddressField;
    InputField* _serverPortField;
    InputField* _playerNameField;
};


#endif //CONNECTIONPANEL_H
