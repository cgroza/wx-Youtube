#include "PrefWindow.hpp"
#include "Enums.hpp"


PrefWindow::PrefWindow(wxWindow* parent): wxFrame(parent, -1, _T("Preferences"))
{
	wxPoint(100,100), wxSize(200,200);
	
	
	wxRadioButton* radioButton1 = new wxRadioButton(this, ID_RADIOBUTTON1, wxT("&I'm still thinking of a preference option"), wxDefaultPosition,
																		     wxDefaultSize);
	//I had a problem with the above code, but I resolved it. Turns out that I was attaching it to the parent window, instaed of "this".																	     
																		     
	radioButton1->SetValue(true);
	
	pref_sizer = new wxBoxSizer(wxHORIZONTAL);
	pref_sizer->Add(radioButton1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	SetSizer(pref_sizer);
	//pref_sizer->Fit(this);
	
	
}


//I don't get how this is included, it works, but I don't get it. Your gonna have to explain it to me :)
