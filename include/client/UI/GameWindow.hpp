// Copied from Lama example Project

#ifndef DIGITALUNO_UI_GAMEWINDOW_H
#define DIGITALUNO_UI_GAMEWINDOW_H

#include "ConnectionPanel.hpp"


class GameWindow : public wxFrame
{
public:
    GameWindow(const wxString& title, const wxPoint& pos, const wxSize& size);

    void showPanel(wxPanel* panel);
    void setStatus(const std::string& message);

private:
    wxBoxSizer* _mainLayout;
    wxStatusBar* _statusBar;
public:
    wxPanel* _currentPanel;

};


#endif //DIGITALUNO_UI_GAMEWINDOW_H
