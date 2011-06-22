#ifndef PREFWINDOW_H
#define PREFWINDOW_H

#include <wx/wx.h>
#include <wx/stattext.h>

class PrefWindow: public wxFrame
{
    public:
        PrefWindow(wxWindow* parent);
        
        wxBoxSizer* pref_sizer;
	wxTextCtrl *save_directory;
	wxString save_dir();
	wxStaticText *save_directory_label;
	

    protected:
    private:
};

#endif // PREFWINDOW_H
