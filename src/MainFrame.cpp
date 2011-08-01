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
    splitter_win -> SetMinimumPaneSize(1);
    upper_panel = new wxPanel(splitter_win);
    lower_panel = new wxPanel(splitter_win);
    lower_notebook = new wxNotebook(lower_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    description = new VideoDescription(lower_notebook, event_manager, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    comments_board = new CommentsBoard(lower_notebook, event_manager, wxID_ANY);

    lower_notebook -> AddPage(description, wxT("Description"));
    lower_notebook -> AddPage(comments_board, wxT("Comments Board"));    

    //Combo box, (option box), to give the user a more specific search
    combo_box = new wxComboBox(upper_panel, ID_COMBOBOX, wxT("Videos"), wxDefaultPosition,
			       wxDefaultSize, choice_string, wxCB_READONLY);

    combo_box -> SetSelection(0); //initially, it is set to -1
    //Search box, this is where the user types in the url, user name, or other relevant info.
    search_box = new wxTextCtrl(upper_panel, TEXT_Search, wxT(""), wxDefaultPosition, wxSize(-1,-1),
				wxTE_RICH | wxTE_PROCESS_ENTER , wxDefaultValidator, wxTextCtrlNameStr);

    //Go Button, this initiates the search
    go_button = new wxButton(upper_panel, BUTTON_Go, _T("Go"), wxDefaultPosition, wxDefaultSize);
    
    download_button = new wxButton(upper_panel, BUTTON_Download, _T("Download"), wxDefaultPosition, wxDefaultSize);

    //List control, this contains the video information
    video_list = new VideoListCtrl(upper_panel);
    //List control initial items

    box_sizer = new wxBoxSizer(wxHORIZONTAL);

    box_sizer->Add(search_box,
		   1,
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

    splitter_win -> SplitHorizontally(upper_panel, lower_panel, -1); // split the window in 2

    //Menu Bar
    MainMenu = new wxMenuBar();
    wxMenu *FileMenu = new wxMenu();
    wxMenu *EditMenu = new wxMenu();

    //Edit Menu functions
    EditMenu->Append(MENU_Pref, wxT("&Preferences\tCTRL+P"), wxT("Edit your preferences"));

    //File Menu functions
    FileMenu->Append(MENU_About, wxT("&About"), wxT("About youtube-wx"));
    FileMenu->Append(MENU_Quit, wxT("&Quit\tCTRL+Q"), wxT("Quit the program"));

    MainMenu->Append(FileMenu, wxT("&File"));
    MainMenu->Append(EditMenu, wxT("&Edit"));

    SetMenuBar(MainMenu);
    // create preferences window
    pref = new PrefWindow(this);

    CreateStatusBar();
    SetStatusText(_("wx-Youtube, version 1.0 alpha")); //"youtube-wx version %s" % (_WXYT_VERSION))

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

void MainFrame::OnSearch(wxCommandEvent& WXUNUSED(event))
{
    wxString search_value  = search_box->GetValue(); //get search string
    SearchURL search_url(getSearchType(), search_value); //make URL with search string
    //get the search results
    XMLFeed feed(&search_url);

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
	event_manager -> FireVideosDeleteEvent(&event);

    }

    if (feed.fetchFeed()) //fetch youtube xml feed
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
    }
    else //something went wrong
    {
	switch (feed.getErrorCode()){ // recovering the curl exit code
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
	return;    // abbort the function
    }

    // delete listed_videos;
    video_list -> DeleteAllItems(); //prepare list for new entry stream

    VideoSearchEvent event(listed_videos);
    event_manager -> FireVideoSearchEvent(&event);    
    //vector iterator
    std::vector<VideoInfo*>::iterator p = listed_videos -> begin();
    // add the items one by one
    // if the vector is empty, there will be no problem
    for(p; p < listed_videos -> end(); ++p){
        video_list -> AddVideo(*p);

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
	current_video.extension =  Extract::return_ext("best");
	
	
	std::cout << "Best format: " << current_video.extension << std::endl;
	std::cout << "Real url: " << current_video.actual_url << std::endl;
	
	
	
	wxString title(current_video.title.c_str(), wxConvUTF8);
	wxString ext(current_video.extension.c_str(), wxConvUTF8);
	
	if (current_video.extension == "") { return; }
	
	wxFileDialog path_dlg(this, wxT("Chose a download folder"), wxT(""), title, ext, wxFD_SAVE);
	
	path_dlg.ShowModal();
	
	current_video.save_dir = path_dlg.GetDirectory().mb_str();
	
	

	current_video.full_save_path = std::string(
	    path_dlg.GetPath().mb_str()).append(".").append(current_video.extension);

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
	event_manager -> FireVideoSelectEvent(&evt);
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

    if(combo_box -> GetCurrentSelection() == 2) download_button -> Disable();
    else download_button -> Enable();
    event.Skip();

}
