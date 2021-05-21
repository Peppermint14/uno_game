// Copied from Lama example Project

#ifndef DIGITALUNO_UI_DIGITALUNO_HPP
#define DIGITALUNO_UI_DIGITALUNO_HPP

#include <wx/wx.h>
#include "UI/GameWindow.hpp"
#include "player_controller.hpp"

player_controller* controller;

// Main app class
class digital_UNO : public wxApp
{
public:
    virtual bool OnInit();

//private: 
   //player_controller* _player_controller;
    
   virtual int OnExit();
};


#endif //DIGITALUNO_UI_DIGITALUNO_HPP
