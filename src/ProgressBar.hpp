#ifndef PROGRESS_BAR_HPP
    #define PROGRESS_BAR_HPP

#include <wx/gauge.h>


class ProgressBar : public wxGauge
{
/* This class will serve as progress indicator and it includes a curl progress callback function.  */


public:
    ProgressBar( wxWindow* parent, wxWindowID id, int range, const wxString& name, const wxPoint& pos = wxDefaultPosition,
		 const wxSize& size = wxDefaultSize, long style = wxGA_HORIZONTAL, 
		 const wxValidator& validator = wxDefaultValidator);

    void Update(int range); 
    static int CurlProgressCallback(void* ptr, double total_dl, double dled_now , double total_upl  , double upled_now);


protected:
private:
    static  ProgressBar* self; 	// static reference to itself to be accessed by static functions.
    static int progress; 
};


#endif	// PROGRESS_BAR_HPP

