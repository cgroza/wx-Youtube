#include "VideoDescription.hpp"

VideoDescription::VideoDescription(wxWindow* parent,  EventManager* evt_man, const wxWindowID id,
	   const wxPoint& pos, const wxSize& size ): wxPanel(parent, id, pos, size)
{
    selected_video_event  = new OnSelectedVideoCall(this);
    deleted_video_event  = new OnDeletedVideoCall(this);

    //initialize dled_thumbnails vector
    dled_thumbnails = new std::vector<std::string>();

    m_sizer = new wxBoxSizer(wxHORIZONTAL);
    // create controls and set the layout
    m_thumbnail_frame = new ThumbnailFrame(this);
    m_descr = new wxTextCtrl(this, wxID_ANY, wxT("Description") ,wxDefaultPosition, wxDefaultSize,
            wxTE_READONLY | wxBORDER_SUNKEN | wxTE_RICH | wxTE_MULTILINE, wxDefaultValidator, wxTextCtrlNameStr);

    m_sizer -> Add(m_descr, 2, wxEXPAND | wxALL, 0);
    m_sizer -> Add(m_thumbnail_frame, 1, wxEXPAND | wxALL, 0);

    SetSizerAndFit(m_sizer);
    // bind events
    evt_man -> BindSelectVideoEvent(selected_video_event);
    evt_man -> BindDeleteVideosEvent(deleted_video_event);

}

ThumbnailFrame* VideoDescription::GetThumbnailFrame() const
{
    return m_thumbnail_frame;
}

wxTextCtrl* VideoDescription::GetDescription() const
{
    return m_descr;
}

void VideoDescription::OnSearch(VideoSearchEvent& event){}
void VideoDescription::OnVideoSelect(VideoSelectEvent& event)
{
    VideoInfo* info = event.GetVideoInfo();
    // the video selection has changed, clear the thumbnail frame
     m_thumbnail_frame -> Clear();
    //display it's description
     m_descr -> SetValue(wxString( info -> getDescription().c_str(), wxConvUTF8));
        //else std::cout<<"FAILED"<<std::endl;

    // download thumbnail 
    // create a thread to start a pararel download

    // check if the video has a thumbnail url
    if(info -> getThumbnail() == "N/A") return; // abort, we don't need to continue any longer.

    // check if we have it in the dled vector
    bool dled = (std::find(dled_thumbnails->begin(), dled_thumbnails->end(), info->getId()) != dled_thumbnails->end());

    if(! dled)
    {
        std::string path(std::string(wxStandardPaths::Get().GetTempDir().mb_str()) + "/" + info -> getId());

	

	DownloadThread* thumb_dl = new DownloadThread(info, info -> getThumbnail(), path,
						      new ThumbnailDownloadCallback(m_thumbnail_frame));

	thumb_dl -> Create();
	thumb_dl -> Run();

	Layout();
	// add this video's ID to the available thumbnails to avoid re-download.
	dled_thumbnails -> push_back( info -> getId() );

    }
    // show thumbnail, will be probably implemented in the callback function of the DownoladThread


}
void VideoDescription::OnDeleteVideos(VideosDeleteEvent& event)
{
    m_thumbnail_frame -> Clear();   //reset thumbnail pictre
    dled_thumbnails -> clear();	    // we will not need these images anymore
    m_descr -> SetValue(wxT("Description"));
}
