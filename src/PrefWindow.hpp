#ifndef PREFWINDOW_H
#define PREFWINDOW_H

#include <wx/wx.h>

class PrefWindow: public wxFrame
{
    public:
        PrefWindow(wxWindow* parent);
        
        wxBoxSizer* pref_sizer;

    protected:
    private:
};

#endif // PREFWINDOW_H
