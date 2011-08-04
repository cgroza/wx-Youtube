#ifndef PREFWINDOW_H
#define PREFWINDOW_H

#include <wx/wx.h>
#include <wx/stattext.h>
#include "CfgManager.hpp"
#include <string>
#include <wx/filepicker.h>
#include <wx/checkbox.h>


class PrefWindow: public wxFrame
{
public:
    PrefWindow(wxWindow* parent,  CfgManager* cfg_man);



private:
        
    wxBoxSizer* pref_sizer;

    wxRadioButton* rd_save_dir;
    wxRadioButton* rd_ask_on_dl;

    wxStaticText *save_directory_label;
    wxDirPickerCtrl* dir_picker;

    wxCheckBox* chk_comments_brd;
    wxCheckBox* chk_vid_descr;
    CfgManager* m_cfg_man;

    void OnRdSaveDir(wxCommandEvent& event);
    void OnRdAskOnDl(wxCommandEvent& event);
    void OnFPChangeFile(wxFileDirPickerEvent& event);
    void OnChkBxCommentsBrd(wxCommandEvent& event);
    void OnChkBxVidDescr(wxCommandEvent& event);

    enum
    {
	DIRPICKER_save_dir,
	RADIO_save_dir,
	RADIO_ask_on_dl,
	CHKBOX_comments_brd,
	CHKBOX_vid_descr,
	
    };
    DECLARE_EVENT_TABLE();
};

#endif // PREFWINDOW_H
