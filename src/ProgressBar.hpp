//Copyright (C) 2011  Groza Cristian, N3
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



#ifndef PROGRESS_BAR_HPP
    #define PROGRESS_BAR_HPP

#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/app.h>
#include "MainFrame.hpp"



class ProgressBar : public wxPanel
{
/* This class will serve as progress indicator and it includes a curl progress callback function.  */


public:
    ProgressBar( wxWindow* parent, wxWindowID id, int range, const wxString& name, wxButton* dlbt, const wxPoint& pos = wxDefaultPosition,
		 const wxSize& size = wxDefaultSize, long style = wxGA_HORIZONTAL, 
		 const wxValidator& validator = wxDefaultValidator);

    void Update(int range); 
    static int CurlProgressCallback(void* ptr, double total_dl, double dled_now , double total_upl  , double upled_now);

protected:
    wxGauge* gauge;
    wxButton* cancel_bt;
    wxButton* dlbutton;
    wxBoxSizer* h_sizer;
    static int curl_callback_code;
    DECLARE_EVENT_TABLE()

    
    enum
	{
	    ID_CANCEL_BUTTON
	};

    void OnCancel(wxCommandEvent& event);

private:
    static  ProgressBar* self; 	// static reference to itself to be accessed by static functions.

};


#endif	// PROGRESS_BAR_HPP

