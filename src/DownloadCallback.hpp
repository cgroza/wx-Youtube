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



#ifndef DOWNLOAD_CALLBACK_H
    #define DOWNLOAD_CALLBACK_H
#include "VideoInfo.hpp"
#include "ThumbnailFrame.hpp"
#include <string>
#include "XMLFeed.hpp"

class DownloadCallback
{
public:
    virtual void operator()(VideoInfo* video_data, std::string& path) = 0;
};

class ThumbnailDownloadCallback: public DownloadCallback
{
public:
    ThumbnailDownloadCallback(ThumbnailFrame* thumb_obj);
    virtual void operator()(VideoInfo* video_data, std::string& path);
private:
    ThumbnailFrame* m_thumb_obj;
};

class ResetWidgetCallback: public DownloadCallback
{
public:
    ResetWidgetCallback(wxWindow* dl_button, wxWindow* progress_bar);
  virtual void operator()(VideoInfo* , std::string& ); // dummy prototype
protected:
    wxWindow* m_dlbutton;
    wxWindow* m_progress_bar;
};

class FeedFetcherCallback
{
public:
    virtual void operator()(rapidxml::xml_document<>*, int) = 0;
};

#endif	// DOWNLOAD_CALLBACK_H
