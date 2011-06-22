#include "ProgressBar.hpp"
#include <iostream>

ProgressBar::ProgressBar(wxWindow* parent, wxWindowID id, int range, const wxString& name, const wxPoint& pos ,
			 const wxSize& size , long style, 
			 const wxValidator& validator):
    wxGauge(parent, id, range, pos, size, style, validator, name)
{
    self = this;
}

void ProgressBar::Update(int val)
{

    wxGauge::SetValue(val);

}

int ProgressBar::CurlProgressCallback(void* ptr, double total_dl, double dled_now , double total_upl  , double upled_now)
{
    if (total_dl > 0) 		// avoid division by zero
    {
	int percentage = (dled_now / total_dl) * 100; // calculate %
	std::cout << percentage  << std::endl;
	self -> Update(percentage);

    }
    return 0;
}

ProgressBar* ProgressBar::self = 0; // default
int ProgressBar::progress = -1;	    // default
