#ifndef PREFWINDOW_H
#define PREFWINDOW_H

#include <wx/wx.h>
#include <wx/stattext.h>
#include "CfgManager.hpp"
#include <string>

class PrefWindow: public wxFrame
{
public:
    PrefWindow(wxWindow* parent,  CfgManager* cfg_man);



private:
        
    wxBoxSizer* pref_sizer;

    wxRadioButton* rd_save_dir;
    wxRadioButton* rd_ask_on_dl;

    wxTextCtrl *save_directory;
    wxStaticText *save_directory_label;
    wxButton* bt_save_dir;
    CfgManager* m_cfg_man;
    void OnRdSaveDir(wxCommandEvent& event);
    void OnRdAskOnDl(wxCommandEvent& event);
    void OnBtSaveDir(wxCommandEvent& event);
    

    enum
    {
	TEXT_save_directory,
	RADIO_save_dir,
	RADIO_ask_on_dl,
	BUTTON_save_dir,
	
    };
    DECLARE_EVENT_TABLE();
};

#endif // PREFWINDOW_H
