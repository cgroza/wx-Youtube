#ifndef PREFWINDOW_H
#define PREFWINDOW_H

#include <wx/wx.h>
#include <wx/stattext.h>
#include "CfgManager.hpp"


class PrefWindow: public wxFrame
{
public:
    PrefWindow(wxWindow* parent, const CfgManager* cfg_man);

        
    wxBoxSizer* pref_sizer;

    wxRadioButton* rd_save_dir;
    wxRadioButton* rd_ask_on_dl;

    wxTextCtrl *save_directory;
    wxString save_dir();
    wxStaticText *save_directory_label;
    wxButton* save_dir_bt;

protected:
private:
    enum
    {
	TEXT_save_directory,
	RADIO_save_dir,
	RADIO_ask_on_dl,
	BUTTON_save_dir,
	
    };
};

#endif // PREFWINDOW_H
