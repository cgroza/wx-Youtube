#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include "wx-youtube.hpp"

class MainFrame: public wxFrame
{
public:

    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSearch(wxCommandEvent& event);
    void OnPref(wxCommandEvent& event);

    wxFrame* pref_window;
    wxButton *go_button;
    wxTextCtrl *search_box;
    wxMenuBar *MainMenu;
    wxComboBox *combo_box;
    wxListCtrl *video_list;

    DECLARE_EVENT_TABLE()
};



enum
{
    TEXT_Search = wxID_HIGHEST + 1,
    MENU_Quit = 1,
    MENU_About,
    MENU_Pref,
    BUTTON_Go,
    ID_COMBOBOX,
    LIST_Video_list,
};


#endif
