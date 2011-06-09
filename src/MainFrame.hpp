#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/splitter.h>
#include "VideoSearch.hpp"
#include "VideoListCtrl.hpp"
#include "Enums.hpp"
#include "SearchURL.hpp"
#include "PrefWindow.hpp"
#include <iostream>
#include "DownloadThread.hpp"


class MainFrame: public wxFrame
{
public:

    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSearch(wxCommandEvent& event);
    void OnPref(wxCommandEvent& event);
    void OnVideoSelect(wxListEvent& event);
    void OnVideoWatch(wxListEvent& event);

    SearchType getSearchType();

    std::vector<VideoInfo*>* listed_videos;

    wxSplitterWindow* splitter_win;

    wxPanel* upper_panel;
    wxBoxSizer* box_sizer;
    wxBoxSizer* topsizer;

    wxPanel* lower_panel;
    wxBoxSizer* lower_sizer;

    wxButton *go_button;
    wxTextCtrl *search_box;
    wxMenuBar *MainMenu;
    wxComboBox *combo_box;
    wxTextCtrl* video_descr;

    VideoListCtrl *video_list;

    PrefWindow* pref;
    DECLARE_EVENT_TABLE()
};





#endif
