#include "ProgressBar.hpp"
#include <iostream>

ProgressBar::ProgressBar(const wxString& title, const wxString& message, int maximum, wxWindow * parent, int style):
    wxProgressDialog(title, message, maximum, parent, style)
{
    self = this;
}


void ProgressBar::CurlProgressCallback(void* ptr, double total_dl, double dled_now , double total_upl  , double upled_now)
{
    if (total_dl > 0) 		// avoid division by zero
{
	int percentage = (dled_now / total_dl) * 100; // calculate %
	std::cout << percentage  << std::endl;
	if(percentage != progress)
	{
	    progress = percentage;
	    self -> Update(percentage);
	}
    }
}

ProgressBar* ProgressBar::self = 0; // default
int ProgressBar::progress = -1;	    // default
