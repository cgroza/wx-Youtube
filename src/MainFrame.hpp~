#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include "wx-youtube.hpp"
#include "VideoListCtrl.hpp"
#include "Enums.hpp"

class MainFrame: public wxFrame
{
public:

    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSearch(wxCommandEvent& event);
    void OnPref(wxCommandEvent& event);

    std::vector<VideoInfo*>* listed_videos;
    wxButton *go_button;
    wxTextCtrl *search_box;
    wxMenuBar *MainMenu;
    wxComboBox *combo_box;
    VideoListCtrl *video_list;

    DECLARE_EVENT_TABLE()
};





#endif
