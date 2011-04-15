
#ifndef MAINAPP_H
#define MAINAPP_H

#include <wx/wx.h>
#include "MainFrame.hpp"


class MainApp: public wxApp
{
    virtual bool OnInit();
};



IMPLEMENT_APP(MainApp)

#endif
