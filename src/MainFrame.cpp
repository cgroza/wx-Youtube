#include "MainFrame.hpp"



MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, -1, title, pos, size)
{


    //Here we will define our controls


    //Combo box options
    wxArrayString choice_string;
    choice_string.Add(wxT("Search"));
    choice_string.Add(wxT("User videos"));
    choice_string.Add(wxT("Playlist"));

    splitter_win = new wxSplitterWindow(this);
    splitter_win -> SetMinimumPaneSize(1);
    upper_panel = new wxPanel(splitter_win);
    lower_panel = new wxPanel(splitter_win);

    //Combo box, (option box), to give the user a more specific search
    combo_box = new wxComboBox(upper_panel, ID_COMBOBOX, wxT("Search"), wxDefaultPosition, wxDefaultSize, choice_string, wxCB_READONLY);

    //Search box, this is where the user types in the url, user name, or other relevant info.
    search_box = new wxTextCtrl(upper_panel, TEXT_Search, wxT("Search"), wxDefaultPosition, wxSize(-1,-1),
				    wxTE_RICH | wxTE_PROCESS_ENTER , wxDefaultValidator, wxTextCtrlNameStr);

    //Go Button, this initiates the search
    go_button = new wxButton(upper_panel, BUTTON_Go, _T("Go"), wxDefaultPosition, wxDefaultSize);

    //List control, this contains the video information
    video_list = new VideoListCtrl(upper_panel);
    //List control initial items

    video_descr = new wxTextCtrl(lower_panel, wxID_ANY, wxT("Video description.") ,wxDefaultPosition, wxSize(-1, -1),
            wxTE_READONLY | wxBORDER_SUNKEN | wxTE_RICH | wxTE_MULTILINE, wxDefaultValidator, wxTextCtrlNameStr);


    box_sizer = new wxBoxSizer(wxHORIZONTAL);

    box_sizer->Add(search_box,
			     1,
			     wxEXPAND |
			     wxALL,
			     0);


    box_sizer->Add(combo_box,
			    0, 			//make vertically strechable
			    wxEXPAND  | //make horizontally stretchable
			    wxALL, 		//and make border all around
			    0);			//set border width to 0


    box_sizer->Add(go_button,
			    0,
			    wxEXPAND |
			    wxALL,
			    0);



    topsizer = new wxBoxSizer(wxVERTICAL);

    topsizer->Add(box_sizer,
			    0,
			    wxEXPAND |
			    wxALIGN_CENTER);


    topsizer->Add(video_list,
			    1,
			    wxEXPAND |
			    wxALL,
			    0);

    upper_panel -> SetSizerAndFit(topsizer);

    lower_sizer = new wxBoxSizer(wxHORIZONTAL);

    lower_sizer-> Add( video_descr,
                    1,
                    wxEXPAND | wxALL,
                    0);

    lower_panel -> SetSizerAndFit(lower_sizer);

    splitter_win -> SplitHorizontally(upper_panel, lower_panel, -1);

    //Menu Bar
    MainMenu = new wxMenuBar();
    wxMenu *FileMenu = new wxMenu();
    wxMenu *EditMenu = new wxMenu();


    //Edit Menu functions
    EditMenu->Append(MENU_Pref, wxT("&Preferences..."), wxT("Edit your preferences"));

    //File Menu functions
    FileMenu->Append(MENU_About, wxT("&About..."), wxT("About youtube-wx"));
    FileMenu->Append(MENU_Quit, wxT("&Quit"), wxT("Quit the program"));



    MainMenu->Append(FileMenu, wxT("&File"));
    MainMenu->Append(EditMenu, wxT("&Edit"));

    SetMenuBar(MainMenu);
    CreateStatusBar();
    SetStatusText(_("youtube-wx, version 0.0.1")); //"youtube-wx version %s" % ("0.0.1"))




}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(MENU_Quit, MainFrame::OnQuit)
    EVT_MENU(MENU_About, MainFrame::OnAbout)
    EVT_MENU(MENU_Pref, MainFrame::OnPref)
    EVT_BUTTON(BUTTON_Go, MainFrame::OnSearch)
    EVT_CHOICE(ID_COMBOBOX, MainFrame::OnSearch)
    EVT_RADIOBUTTON(ID_RADIOBUTTON1, MainFrame::OnAbout)
    EVT_LIST_ITEM_SELECTED(LIST_Video_list, MainFrame::OnVideoSelect)
    EVT_TEXT_ENTER(TEXT_Search, MainFrame::OnSearch)
END_EVENT_TABLE()



void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(_("Small utility to download youtube videos, based off of youtube-dl"),
        _("About Youtube-wx"),
        wxOK | wxICON_INFORMATION, this);
}

void MainFrame::OnPref(wxCommandEvent& WXUNUSED(event))
{
	PrefWindow *pref = new PrefWindow(this);

	pref->Show(true);

	return;
}

void MainFrame::OnSearch(wxCommandEvent& WXUNUSED(event))
{
    wxString search_value;
    search_value = search_box->GetValue();
    SearchURL search_url(VIDEO_SEARCH, search_value);
    //get the search results
    VideoSearch video_search(&search_url);

    if (video_search.doSearch())
    {
        listed_videos = video_search.getSearchResults();
    }else
    {
        switch (video_search.getCurlCode()){
		case 6:
			wxMessageBox(_("Could not resolve host"), _("Error"), wxOK | wxICON_INFORMATION);
			break;
		case 7:
			wxMessageBox(_("Could not connect"), 	  _("Error"), wxOK | wxICON_INFORMATION);
			break;
		case 28:
			wxMessageBox(_("Operation timed out"),    _("Error"), wxOK | wxICON_INFORMATION);
			break;
		case 52:
			wxMessageBox(_("Got nothing"), 			  _("Error"), wxOK | wxICON_INFORMATION);
			break;
		case 56:
			wxMessageBox(_("Recieve error"),          _("Error"), wxOK | wxICON_INFORMATION);
			break;
		default:
			wxMessageBox(_("Undocumented error"),     _("Error"), wxOK | wxICON_INFORMATION);
			break;
			}
        return;
        }


    video_list -> DeleteAllItems();

    //vector iterator
    std::vector<VideoInfo*>::iterator p = listed_videos -> begin();
    //add the items one by one
    for(p; p != listed_videos -> end(); ++p){
        video_list -> AddVideo(*p);

    }

}




void MainFrame::OnVideoSelect(wxListEvent& event)
{
    long video_item_index = video_list -> GetFirstSelected () ;
    if (video_item_index != -1){

        VideoEntry* item = video_list -> GetVideoEntry(video_item_index);
        video_descr -> SetValue(wxString(item -> getVideoData() -> getDescription().c_str(), wxConvUTF8));
        //else std::cout<<"FAILED"<<std::endl;
    }
    event.Skip();
}


