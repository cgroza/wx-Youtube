#include "PrefWindow.hpp"
#include "Enums.hpp"



PrefWindow::PrefWindow(wxWindow* parent): wxFrame(parent, -1, _T("Preferences"))
{
	wxPoint(100,100), wxSize(200,200);
	
	
	//wxRadioButton* radioButton1 = new wxRadioButton(this, ID_RADIOBUTTON1, wxT("&I'm still thinking of a preference option"), wxDefaultPosition, wxDefaultSize);
															  

	rd_save_dir = new wxRadioButton(this, wxID_ANY, wxT("Save in predefined folder:"));
	rd_ask_on_dl = new wxRadioButton(this, wxID_ANY, wxT("Ask on downoload"));
	save_directory = new wxTextCtrl(this, TEXT_save_directory, wxT("/tmp"), wxPoint(1,1), wxSize(250,-1),
                                    wxTE_RICH | wxTE_PROCESS_ENTER , wxDefaultValidator, wxTextCtrlNameStr);

	
	save_directory_label = new wxStaticText(this, wxID_ANY, wxT("Directory to save videos"), wxDefaultPosition, wxDefaultSize);
																		     
	
	
	pref_sizer = new wxBoxSizer(wxVERTICAL);
	pref_sizer->Add(rd_save_dir, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	pref_sizer->Add(save_directory_label, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	pref_sizer->Add(save_directory, 0 ,wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	pref_sizer->Add(rd_ask_on_dl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);	

	SetSizer(pref_sizer);
	pref_sizer->Fit(this);
	
	
}


wxString PrefWindow::save_dir()
{
    //wxString search_value  = search_box->GetValue();
    wxString wat = save_directory->GetValue();
    return wat;
};
