#include "ProgressBar.hpp"


ProgressBar::ProgressBar(const wxString& title, const wxString& message, int maximum, wxWindow * parent, int style):
    wxProgressDialog(title, message, maximum, parent, style)
{
    self = this;
}


void ProgressBar::CurlProgressCallback(void* ptr, double total_dl, double dled_now , double total_upl  , double upled_now)
{
    int percentage = (dled_now / total_dl) * 100; // calculate %
    self -> Update(percentage);
}

ProgressBar* ProgressBar::self = 0; // default
