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



#include "PrefWindow.hpp"

PrefWindow::PrefWindow(wxWindow* parent,  CfgManager* cfg_man): wxFrame(parent, -1, _T("Preferences")), m_cfg_man(cfg_man)
{
    wxPoint(100,100), wxSize(200,200);
	
	
    //wxRadioButton* radioButton1 = new wxRadioButton(this, ID_RADIOBUTTON1, wxT("&I'm still thinking of a preference option"), wxDefaultPosition, wxDefaultSize);
															  

    rd_save_dir = new wxRadioButton(this, RADIO_save_dir, wxT("Save In Predefined Folder:"));
    rd_ask_on_dl = new wxRadioButton(this, RADIO_ask_on_dl, wxT("Ask On Download"));
    if(m_cfg_man -> GetOption("ask_save_path_on_download") -> value == "True") 
    {
	rd_save_dir -> SetValue(false);
	rd_ask_on_dl -> SetValue(true);
    }

    wxString cfg_save_dir = wxString(m_cfg_man -> GetOption("video_save_dir") -> value.c_str(), wxConvUTF8);
    dir_picker = new wxDirPickerCtrl(this, DIRPICKER_save_dir, cfg_save_dir);
	
    save_directory_label = new wxStaticText(this, wxID_ANY, wxT("Directory to save videos"), wxDefaultPosition, wxDefaultSize);

    chk_comments_brd = new wxCheckBox(this, CHKBOX_comments_brd, wxT("Enable Comments Board"));
    chk_comments_brd -> SetValue(m_cfg_man -> GetOption("comments_board") -> value == "True");

    chk_vid_descr = new wxCheckBox(this, CHKBOX_vid_descr, wxT("Enable Video Description"));
    chk_vid_descr -> SetValue(m_cfg_man -> GetOption("video_description") -> value == "True");

    pref_sizer = new wxBoxSizer(wxVERTICAL);
    pref_sizer->Add(rd_save_dir, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    pref_sizer->Add(save_directory_label, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    pref_sizer->Add(dir_picker, 0 ,wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    pref_sizer->Add(rd_ask_on_dl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);	
    pref_sizer->Add(chk_comments_brd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);	
    pref_sizer->Add(chk_vid_descr, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    SetSizer(pref_sizer);
    pref_sizer->Fit(this);
	
}

void PrefWindow::OnRdSaveDir(wxCommandEvent& event)
{
    m_cfg_man -> SetOption("ask_save_path_on_download", "False");
    m_cfg_man -> SetOption("video_save_dir", std::string(dir_picker -> GetPath().mb_str()));
    dir_picker -> Enable();


}

void PrefWindow::OnRdAskOnDl(wxCommandEvent& event)
{
    m_cfg_man -> SetOption("ask_save_path_on_download", "True");
    dir_picker -> Disable();

}

void PrefWindow::OnFPChangeFile(wxFileDirPickerEvent& event)
{
    m_cfg_man -> SetOption("video_save_dir", std::string(dir_picker -> GetPath().mb_str()));
}

void PrefWindow::OnChkBxCommentsBrd(wxCommandEvent& event)
{
    std::string opt_value;
    if(chk_comments_brd -> GetValue()) opt_value = "True";
    else opt_value = "False";

    m_cfg_man -> SetOption("comments_board", opt_value);
}

void PrefWindow::OnChkBxVidDescr(wxCommandEvent& event)
{
    std::string opt_value;
    if(chk_comments_brd -> GetValue()) opt_value = "True";
    else opt_value = "False";

    m_cfg_man -> SetOption("video_description", opt_value);
}

void PrefWindow::OnClose(wxCloseEvent& event)
{
    Hide();			// do not destoy window on close, hide it instead.
}

BEGIN_EVENT_TABLE(PrefWindow, wxFrame)
EVT_RADIOBUTTON(RADIO_save_dir, PrefWindow::OnRdSaveDir)
EVT_RADIOBUTTON(RADIO_ask_on_dl, PrefWindow::OnRdAskOnDl)
EVT_DIRPICKER_CHANGED(DIRPICKER_save_dir, PrefWindow::OnFPChangeFile)
EVT_CHECKBOX(CHKBOX_comments_brd, PrefWindow::OnChkBxCommentsBrd)
EVT_CHECKBOX(CHKBOX_vid_descr, PrefWindow::OnChkBxVidDescr)
EVT_CLOSE(PrefWindow::OnClose)
END_EVENT_TABLE()
