#include <wx/wxprec.h>
#include <wx/wx.h>
#include <nlohmann/json.hpp>
#include <sockpp/tcp_socket.h>
#include <wx/app.h>
#include "../../include/client/digital_UNO.hpp"
#include "../../include/client/player_controller.hpp"
#include "../../include/client/tcp_client.hpp"

// Macro which will generate a main function which serves as entry point into the program
wxIMPLEMENT_APP(digital_UNO);
