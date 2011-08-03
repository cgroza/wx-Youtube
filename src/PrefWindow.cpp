#include "PrefWindow.hpp"

PrefWindow::PrefWindow(wxWindow* parent,  CfgManager* cfg_man): wxFrame(parent, -1, _T("Preferences")), m_cfg_man(cfg_man)
{
    wxPoint(100,100), wxSize(200,200);
	
	
    //wxRadioButton* radioButton1 = new wxRadioButton(this, ID_RADIOBUTTON1, wxT("&I'm still thinking of a preference option"), wxDefaultPosition, wxDefaultSize);
															  

    rd_save_dir = new wxRadioButton(this, RADIO_save_dir, wxT("Save In Predefined Folder:"));
    rd_ask_on_dl = new wxRadioButton(this, RADIO_ask_on_dl, wxT("Ask On Download"));

    wxString cfg_save_dir = wxString(m_cfg_man -> GetOption("video_save_dir") -> value.c_str(), wxConvUTF8);
    save_directory = new wxTextCtrl(this, TEXT_save_directory, cfg_save_dir, wxPoint(1,1), wxSize(250,-1),
                                    wxTE_RICH | wxTE_PROCESS_ENTER , wxDefaultValidator, wxTextCtrlNameStr);

	
    save_directory_label = new wxStaticText(this, wxID_ANY, wxT("Directory to save videos"), wxDefaultPosition, wxDefaultSize);
    bt_save_dir = new wxButton(this, BUTTON_save_dir, wxT("Save Directory"));
	
	
    pref_sizer = new wxBoxSizer(wxVERTICAL);
    pref_sizer->Add(rd_save_dir, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    pref_sizer->Add(save_directory_label, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    pref_sizer->Add(save_directory, 0 ,wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    pref_sizer->Add(bt_save_dir, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    pref_sizer->Add(rd_ask_on_dl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);	

    SetSizer(pref_sizer);
    pref_sizer->Fit(this);
	
}

void PrefWindow::OnRdSaveDir(wxCommandEvent& event)
{
    m_cfg_man -> SetOption("ask_save_path_on_download", "False");
    save_directory -> Enable();
    bt_save_dir -> Enable();

}

void PrefWindow::OnRdAskOnDl(wxCommandEvent& event)
{
    m_cfg_man -> SetOption("ask_save_path_on_download", "True");
    save_directory -> Disable();
    bt_save_dir -> Disable();

}

void PrefWindow::OnBtSaveDir(wxCommandEvent& event)
{
    m_cfg_man -> SetOption("video_save_dir", std::string(save_directory -> GetValue().mb_str()));
}

BEGIN_EVENT_TABLE(PrefWindow, wxFrame)
EVT_RADIOBUTTON(RADIO_save_dir, PrefWindow::OnRdSaveDir)
EVT_RADIOBUTTON(RADIO_ask_on_dl, PrefWindow::OnRdAskOnDl)
EVT_BUTTON(BUTTON_save_dir, PrefWindow::OnBtSaveDir)
END_EVENT_TABLE()
