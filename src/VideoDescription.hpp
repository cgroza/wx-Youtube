#ifndef VIDEO_DESCRIPTION_H
     #define VIDEO_DESCRIPTION_H

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/stdpaths.h>
#include "ThumbnailFrame.hpp"
#include "EventHandler.hpp"
#include "EventManager.hpp"
#include "Events.hpp"
#include <vector>
#include <string>
#include "DownloadCallback.hpp"
#include "DownloadThread.hpp"
#include "VideoInfo.hpp"
#include <algorithm>


class VideoDescription : public wxPanel, public EventHandler
/* This class offers the video description and thumbnail display.*/
{
public:
    VideoDescription(wxWindow* parent,  EventManager* evt_man, const wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		     const wxSize& size = wxDefaultSize );

    ThumbnailFrame* GetThumbnailFrame() const;
    wxTextCtrl* GetDescription() const;
    void OnSearch(VideoSearchEvent& event);
    void OnVideoSelect(VideoSelectEvent& event);
    void OnDeleteVideos(VideoDeleteEvent& event);




private:
    wxBoxSizer* m_sizer;
    ThumbnailFrame* m_thumbnail_frame;
    wxTextCtrl* m_descr;
    std::vector<std::string>* dled_thumbnails; // contains video IDs

    class OnSelectedVideoCall : public VideoSelectObjectFunction
    {
    public:
 	OnSelectedVideoCall(VideoDescription* parent): m_parent(parent){}
	virtual void operator()(VideoSelectEvent* event){ m_parent -> OnVideoSelect(*event);}
	    private:
		VideoDescription* m_parent;
    };
    OnSelectedVideoCall* selected_video_event;
};

#endif	// VIDEO_DESCRPTION_H
