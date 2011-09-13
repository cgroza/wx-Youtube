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



#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/stdpaths.h>
#include "XMLFeed.hpp"
#include "VideoListCtrl.hpp"
#include "Enums.hpp"
#include "SearchURL.hpp"
#include "PrefWindow.hpp"
#include "DownloadThread.hpp"
#include <algorithm>
#include "DownloadCallback.hpp"
#include "VideoDescription.hpp"
#include "EventManager.hpp"
#include "Events.hpp"
#include "Extract.hpp"
#include "ProgressBar.hpp"
#include "CommentsBoard.hpp"
#include "AboutInfo.hpp"
#include "CfgManager.hpp"



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
    void OnVideoDownload(wxCommandEvent& event);

    void OnComboBoxSelect(wxCommandEvent& event);

    SearchType getSearchType();

    std::vector<VideoInfo*>* listed_videos;

    wxSplitterWindow* splitter_win;

    wxPanel* upper_panel;
    wxBoxSizer* box_sizer;
    wxBoxSizer* topsizer;

    wxPanel* lower_panel;
    wxBoxSizer* lower_sizer;

    wxButton *go_button;
    wxButton *download_button;
    wxTextCtrl *search_box;
    wxTextCtrl *num_vids;
    wxMenuBar *MainMenu;
    wxComboBox *combo_box;
    wxNotebook *lower_notebook;
    VideoDescription* description;
    CommentsBoard* comments_board;
    VideoListCtrl *video_list;
    EventManager* event_manager;
    CfgManager* cfg_manager;

    PrefWindow* pref;
    DECLARE_EVENT_TABLE()
};





#endif
