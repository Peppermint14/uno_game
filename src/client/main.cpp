// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include "wx/wx.h"
#include <nlohmann/json.hpp>
#include <sockpp/tcp_socket.h>
#include <wx/app.h>
#include "../../include/client/digital_UNO.hpp"

// Macro which will generate a main function which serves as entry point into the program
wxIMPLEMENT_APP(digital_UNO);