#include "MainApp.hpp"

#ifdef MAINAPP_H

bool MainApp::OnInit()
{
    MainFrame *frame = new MainFrame( _("Youtube-wx"), wxPoint(50,50), wxSize(620,540));
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}


#endif
