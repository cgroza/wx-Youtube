#include "PrefWindow.hpp"
#include "Enums.hpp"


PrefWindow::PrefWindow(wxWindow* parent): wxFrame(parent, -1, _T("Preferences"))
{
	wxPoint(100,100), wxSize(200,200);
	
	
	wxRadioButton* radioButton1 = new wxRadioButton(parent, ID_RADIOBUTTON1, wxT("&I'm still thinking of a preference option"), wxDefaultPosition,
																		     wxDefaultSize, wxRB_GROUP);
	radioButton1->SetValue(true);
	
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(radioButton1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
}


//I don't get how this is included, it works, but I don't get it. Your gonna have to explain it to me :)
