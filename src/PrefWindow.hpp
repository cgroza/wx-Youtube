//Copyright (C) 2011  Groza Cristian, N3
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



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
    void OnClose(wxCloseEvent& event); // prevents this window to be destroyed
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
