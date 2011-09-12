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
    void OnDeleteVideos(VideosDeleteEvent& event);




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

    class OnDeletedVideoCall: public VideosDeleteObjectFunction
    {
    public:
	OnDeletedVideoCall(VideoDescription* parent): m_parent(parent){}
	virtual void operator()(VideosDeleteEvent* event){ m_parent -> OnDeleteVideos(*event);}
    private:
	VideoDescription* m_parent;
    };

    OnSelectedVideoCall* selected_video_event;
    OnDeletedVideoCall* deleted_video_event;
};

#endif	// VIDEO_DESCRPTION_H
