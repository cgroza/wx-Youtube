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



#include "MainFrame.hpp"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, -1, title, pos, size)
{
    //Here we will initalize our controls
    // initialize jpeg image handler
    wxInitAllImageHandlers();
    listed_videos = new std::vector<VideoInfo*>();
    event_manager = new EventManager();

    cfg_manager = new CfgManager(std::string(wxStandardPaths::Get().GetDocumentsDir().mb_str()) + "/.wxyoutube" );

    // std::cout << cfg_manager -> GetOption("save_dir") -> value << std::endl;

    //Combo box options
    wxArrayString choice_string;
    choice_string.Add(wxT("Videos"));
    choice_string.Add(wxT("User Videos"));
    choice_string.Add(wxT("Playlist"));


    splitter_win = new wxSplitterWindow(this);
    splitter_win -> SetMinimumPaneSize(200);
    upper_panel = new wxPanel(splitter_win);
    lower_panel = new wxPanel(splitter_win);
    lower_notebook = new wxNotebook(lower_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    
    
    
    //Combo box, (option box), to give the user a more specific search
    combo_box = new wxComboBox(upper_panel, ID_COMBOBOX, wxT("Videos"), wxDefaultPosition,
			       wxDefaultSize, choice_string, wxCB_READONLY);

    combo_box -> SetSelection(0); //initially, it is set to -1
    
    combo_box->SetToolTip(wxT("Change the type of search"));
    
    
    //Search box, this is where the user types in the url, user name, or other relevant info.
    search_box = new wxTextCtrl(upper_panel, TEXT_Search, wxT(""), wxDefaultPosition, wxSize(-1,-1),
				wxTE_RICH | wxTE_PROCESS_ENTER , wxDefaultValidator, wxTextCtrlNameStr);
    
    search_box->SetToolTip(wxT("Search entry"));
    
    				
    num_vids = new wxTextCtrl(upper_panel, TEXT_num_vids, wxT("25"), wxDefaultPosition, wxSize(-1,-1),
				wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
				
    num_vids->SetToolTip(wxT("Number of videos to search for"));
    
    
    
    //Go Button, this initiates the search
    go_button = new wxButton(upper_panel, BUTTON_Go, _T("Go"), wxDefaultPosition, wxDefaultSize);
    
    go_button->SetToolTip(wxT("Search for the videos"));
    
    
    
    download_button = new wxButton(upper_panel, BUTTON_Download, _T("Download"), wxDefaultPosition, wxDefaultSize);
    
    download_button->SetToolTip(wxT("Download the selected video(s)"));

    //List control, this contains the video information
    video_list = new VideoListCtrl(upper_panel);
    //List control initial items

    box_sizer = new wxBoxSizer(wxHORIZONTAL);

    box_sizer->Add(search_box,
		   1,
		   wxEXPAND |
		   wxALL,
		   0);
    
    box_sizer->Add(num_vids,
		   0,
		   wxEXPAND |
		   wxALL,
		   0);
    
    box_sizer->Add(combo_box,
		   0,            //make vertically strechable
		   wxEXPAND  |   //make horizontally stretchable
		   wxALL,        //and make border all around
		   0);           //set border width to 0
    box_sizer->Add(download_button,
		   0,
		   wxEXPAND |
		   wxALL,
		   0);
    
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
    lower_sizer -> Add(lower_notebook, 1, wxEXPAND | wxALL, 0);
    lower_panel -> SetSizerAndFit(lower_sizer);
    // create and add video description and comments board
    // check config first
    if(cfg_manager -> GetOption("video_description") -> value == "True")
    {
	description = new VideoDescription(lower_notebook, event_manager, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	lower_notebook -> AddPage(description, wxT("Description"));
    }

    if(cfg_manager -> GetOption("comments_board") -> value  == "True")
    {
	comments_board = new CommentsBoard(lower_notebook, event_manager, wxID_ANY);
	lower_notebook -> AddPage(comments_board, wxT("Comments Board"));    
    }

    splitter_win -> SplitHorizontally(upper_panel, lower_panel, -1); // split the window in 2
    if(lower_notebook -> GetPageCount() == 0) splitter_win -> Unsplit(); // unsplit the window if notebook is empty


    //Menu Bar
    MainMenu = new wxMenuBar();
    wxMenu *FileMenu = new wxMenu();
    wxMenu *EditMenu = new wxMenu();

    //Edit Menu functions
    EditMenu->Append(MENU_Pref, wxT("&Preferences\tCTRL+P"), wxT("Edit your preferences"));

    //File Menu functions
    FileMenu->Append(MENU_About, wxT("&About"), wxT("About wx-Youtube"));
    FileMenu->Append(MENU_Quit, wxT("&Quit\tCTRL+Q"), wxT("Quit the program"));

    MainMenu->Append(FileMenu, wxT("&File"));
    MainMenu->Append(EditMenu, wxT("&Edit"));

    SetMenuBar(MainMenu);
    // create preferences window
    pref = new PrefWindow(this, cfg_manager);

    CreateStatusBar();
    SetStatusText(_("wx-Youtube, version 1")); //"youtube-wx version %s" % (_WXYT_VERSION))

}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(MENU_Quit, MainFrame::OnQuit)
EVT_MENU(MENU_About, MainFrame::OnAbout)
EVT_MENU(MENU_Pref, MainFrame::OnPref)
EVT_BUTTON(BUTTON_Download, MainFrame::OnVideoDownload)
EVT_BUTTON(BUTTON_Go, MainFrame::OnSearch)
EVT_CHOICE(ID_COMBOBOX, MainFrame::OnSearch)
EVT_RADIOBUTTON(ID_RADIOBUTTON1, MainFrame::OnAbout)
EVT_LIST_ITEM_SELECTED(LIST_Video_list, MainFrame::OnVideoSelect)
EVT_LIST_ITEM_ACTIVATED(LIST_Video_list, MainFrame::OnVideoWatch)
EVT_TEXT_ENTER(TEXT_Search, MainFrame::OnSearch)
EVT_COMBOBOX(ID_COMBOBOX, MainFrame::OnComboBoxSelect)

END_EVENT_TABLE()



void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{

    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    // wxMessageBox(_("Small utility to download youtube videos, based off of youtube-dl"),
    // 		 _("About Youtube-wx"),
    // 		 wxOK | wxICON_INFORMATION, this);

    AboutInfo info;
    wxAboutBox(info);

}

void MainFrame::OnPref(wxCommandEvent& WXUNUSED(event))
{
    pref->Show(true); 	// show the preferences window
    return;
}

void MainFrame::ClearList()
{
        // delete listed_videos;
    video_list -> DeleteAllItems(); //prepare list for new entry stream

    VideoSearchEvent event(listed_videos);
    event_manager -> FireEvent(&event);    
    //vector iterator
    std::vector<VideoInfo*>::iterator p = listed_videos -> begin();
    // add the items one by one
    // if the vector is empty, there will be no problem
    for(p; p < listed_videos -> end(); ++p){
        video_list -> AddVideo(*p);

    }

}

void MainFrame::Error(int error_code)
{
    switch (error_code)
    {
	case 6:
	    wxMessageBox(_("Could not resolve host"), _("Error"), wxOK | wxICON_INFORMATION);
	    break;
	case 7:
	    wxMessageBox(_("Could not connect"),      _("Error"), wxOK | wxICON_INFORMATION);
	    break;
	case 28:
	    wxMessageBox(_("Operation timed out"),    _("Error"), wxOK | wxICON_INFORMATION);
	    break;
	case 52:
	    wxMessageBox(_("Got nothing"),            _("Error"), wxOK | wxICON_INFORMATION);
	    break;
	case 56:
	    wxMessageBox(_("Receive error"),          _("Error"), wxOK | wxICON_INFORMATION);
	    break;
	case NO_SEARCH_RESULT:
	    break;
	default:
	    wxMessageBox(_("Undocumented error"),     _("Error"), wxOK | wxICON_INFORMATION);
	    break;
    }
    
}

void MainFrame::OnSearch(wxCommandEvent& WXUNUSED(event))
{
    DeleteList();
    wxString search_value(Extract::encode_search(std::string(search_box->GetValue().mb_str())).c_str(), wxConvUTF8); //get search string [FIXED]
    
    int vid_num = atoi(num_vids -> GetValue().mb_str());
    int start_index = 1;
    
    std::cout << "Getting a total of: " << vid_num << " videos" << std::endl;
    
    do 
    {
	if (vid_num <= 50) //If there are less than 50 (maximum we can search for)
	{
	    std::cout << "Getting " << start_index << "-" << vid_num << std::endl; 
	    if (Parse(SearchURL(getSearchType(), search_value, start_index, vid_num)))
	    {
		vid_num = 0;
		if (FillList())
		{
		    continue;
		}
	    }
	}
	
	else
	{
	    std::cout << "Getting " << start_index << "-" << 50 << " Left: " << vid_num << std::endl;
	    if (Parse(SearchURL(getSearchType(), search_value, start_index, 50)))
	    {
		start_index += 50;
		vid_num -= 50;
		if (FillList())
		{
		    continue;
		}
	    }
	}
    }
    
    while (vid_num);
    
}


int MainFrame::Parse(SearchURL search_url)
{
    XMLFeed feed(&search_url);
    
    if (feed.fetchFeed())
    {
	switch(search_url.getSearchType())
	{
	    case VIDEO_SEARCH:
	    case USER_VIDEO_SEARCH:
		Parser::parseVideoFeed(listed_videos, feed.getXMLFeed());
		break;

	    case PLAY_LIST_SEARCH:
		Parser::parsePlaylistFeed(listed_videos, feed.getXMLFeed());
		break;
	}
	
    return 1;
    
    }
    
    else
    {
	std::cout << "Error with XMLFeed" << std::endl;
	MainFrame::Error(feed.getErrorCode()); 
	return 0;
    };
    
}
    

int MainFrame::FillList()
{
    std::cout << "Filling list" << std::endl;
    //prepare list for new entry stream
    //vector iterator
    std::vector<VideoInfo*>::iterator p = listed_videos->begin();
    
    /* add the items one by one
    /* if the vector is empty, there will be no problem */
    
    for(p; p < listed_videos -> end(); ++p)
    {
	std::cout << "herp" << std::endl;
	video_list -> AddVideo(*p);
	video_list -> Update();
    }
    
    return 1;
    
}

void MainFrame::DeleteList()
{
    video_list -> DeleteAllItems();
    // delete the the VideoInfo allocated on the heap
    if(listed_videos -> size()){
	std::vector<VideoInfo*>::iterator it = listed_videos -> begin();
	for(it; it != listed_videos -> end(); ++it)
	{
	    delete (*it);
	    *it = 0;
	}

	listed_videos -> clear();
	VideosDeleteEvent event;
	event_manager -> FireEvent(&event);

    }
    
}



void MainFrame::OnVideoDownload(wxCommandEvent& WXUNUSED(event))
{
    long video_item_index = video_list -> GetFirstSelected ();
    std::map<std::string, std::string> real_url;
    if (video_item_index != -1) //if found
    {
	Extract::video_struct current_video;
	VideoEntry* item = video_list -> GetVideoEntry(video_item_index); //get it's video entry object
	VideoInfo*  info = item -> getVideoData();
	// put config check later here, user may have a default directory
	
	current_video.title = info->getName();
	current_video.id = info->getId();
	
	Extract::resolve_real_url(current_video.id); //This needs to be called first, otherwise it won't work. 
	
	current_video.actual_url = Extract::return_url("best"); //This no longer needs to be called first.
	current_video.extension =  Extract::return_ext(current_video.actual_url);
	
	std::cout << "Best format: " << current_video.extension << std::endl;
	std::cout << "Real url: " << current_video.actual_url << std::endl;
	
	wxString title(current_video.title.c_str(), wxConvUTF8);
	wxString ext(current_video.extension.c_str(), wxConvUTF8);
	
	if (current_video.extension == "") { return; }

	CfgManager::CfgOption* option = cfg_manager -> GetOption("ask_save_path_on_download"); // get config option
	if(option)			// check if successfull
	{	
	    if(option -> value == "True")
	    {

		wxFileDialog path_dlg(this, wxT("Chose a download folder"), wxT(""), title, ext, wxFD_SAVE);
	
		if (path_dlg.ShowModal() == wxID_CANCEL) return;
	
		current_video.save_dir = path_dlg.GetDirectory().mb_str();
	
		current_video.full_save_path = std::string(
		    path_dlg.GetPath().mb_str()).append(".").append(current_video.extension);
	    }
	    else
	    {
		current_video.save_dir = cfg_manager -> GetOption("video_save_dir") -> value;
		current_video.full_save_path = current_video.save_dir+"/"+current_video.title+"."+current_video.extension;
	    }	
	}
    
    // current_video.full_save_path = current_video.save_dir+current_video.title+"."+current_video.extension;
	
    std::cout << current_video.full_save_path << std::endl;
    std::cout << "[#]Video id is: " << info -> getId() << std::endl;
    std::cout << "[#]Real url is: " << current_video.actual_url << std::endl;
    std::cout << "[#]Format is: " << current_video.extension << std::endl;
    std::cout << "[#]Full save path: " << current_video.full_save_path << std::endl;

    // create progress bar dialog
    ProgressBar* progress =  new ProgressBar(GetStatusBar(), wxID_ANY, 100,
					     wxT("Downloading, please wait"));
    // disable the download button
    download_button -> Disable();
    // create a callback to reactivate the button after the download is done
    EnableWidgetCallback* callback = new EnableWidgetCallback(download_button);
    //you should atach the ext here, after getting the path
    DownloadThread* video_dl = new DownloadThread(info, current_video.actual_url,current_video.full_save_path,
						  callback, &ProgressBar::CurlProgressCallback);
    progress -> Show();
    video_dl -> Create();
    video_dl -> Run();
    }
}


void MainFrame::OnVideoSelect(wxListEvent& event)
{
    
    long video_item_index = video_list -> GetFirstSelected () ; //get selected video
    if (video_item_index != -1) //if found
    {
	//wxMessageBox(_("Could not resolve host"), _("Error"), wxOK | wxICON_INFORMATION);
    
	VideoEntry* item = video_list -> GetVideoEntry(video_item_index); //get it's video entry object
	VideoInfo*  info = item -> getVideoData();
	VideoSelectEvent evt(info);
	event_manager -> FireEvent(&evt);
    }
    event.Skip();

}

SearchType MainFrame::getSearchType()
{
    int index = combo_box -> GetCurrentSelection(); //get the index from the search 
    //criteria selection box
    switch (index)
    {
    case 0:
	return VIDEO_SEARCH;
	break;
    case 1:
	return USER_VIDEO_SEARCH;
	break;
    case 2:
	return PLAY_LIST_SEARCH;
	break;

    }
}

void MainFrame::OnVideoWatch(wxListEvent& event)
{
    long video_item_index = video_list -> GetFirstSelected () ; //get selected video
    if (video_item_index != -1){ //if found

	VideoEntry* item = video_list -> GetVideoEntry(video_item_index); //get it's video entry object
	std::cout << item -> getVideoData() -> getName() << std::endl;
	std::cout << item -> getVideoData() -> getLink() << std::endl;

	// open the browser to the video entry link
	wxLaunchDefaultBrowser(wxString(item -> getVideoData() -> getLink().c_str(), wxConvUTF8));

    }
    event.Skip();
}

void MainFrame::OnComboBoxSelect(wxCommandEvent& event)
{

    switch(combo_box -> GetCurrentSelection())
    {
    case 2:
	download_button -> Disable();
	break;
    default:
	download_button -> Enable();
    event.Skip();

    }
}
