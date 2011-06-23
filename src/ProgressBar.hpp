#ifndef PROGRESS_BAR_HPP
    #define PROGRESS_BAR_HPP

#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/app.h>

class ProgressBar : public wxPanel
{
/* This class will serve as progress indicator and it includes a curl progress callback function.  */


public:
    ProgressBar( wxWindow* parent, wxWindowID id, int range, const wxString& name, const wxPoint& pos = wxDefaultPosition,
		 const wxSize& size = wxDefaultSize, long style = wxGA_HORIZONTAL, 
		 const wxValidator& validator = wxDefaultValidator);

    void Update(int range); 
    static int CurlProgressCallback(void* ptr, double total_dl, double dled_now , double total_upl  , double upled_now);


protected:
    wxGauge* gauge;
    wxButton* cancel_bt;
    wxBoxSizer* h_sizer;


private:
    static  ProgressBar* self; 	// static reference to itself to be accessed by static functions.

};


#endif	// PROGRESS_BAR_HPP

