#ifndef PROGRESS_BAR_HPP
    #define PROGRESS_BAR_HPP

#include <wx/progdlg.h>


class ProgressBar : public wxProgressDialog
{
/* This class will serve as progress indicator and it includes a curl progress callback function.  */


public:
    ProgressBar(const wxString& title, const wxString& message, int maximum = 100,
		wxWindow * parent = NULL, int style = wxPD_AUTO_HIDE | wxPD_APP_MODAL);

    static void CurlProgressCallback(void* ptr, double total_dl, double dled_now , double total_upl  , double upled_now);


protected:
private:
    static  ProgressBar* self; 	// static reference to itself to be accessed by static functions.
    static int progress; 
};


#endif	// PROGRESS_BAR_HPP

