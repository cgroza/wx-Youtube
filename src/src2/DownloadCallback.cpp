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



#include "DownloadCallback.hpp"
#include "ProgressBar.hpp"


ThumbnailDownloadCallback::ThumbnailDownloadCallback(ThumbnailFrame* thumb_obj): m_thumb_obj(thumb_obj)
{

}

void ThumbnailDownloadCallback::operator()(VideoInfo* video_data, std::string& path)
{

    m_thumb_obj -> ProcessNewThumbnail(video_data, path);
}

ResetWidgetCallback::ResetWidgetCallback(wxWindow* dl_button, wxWindow* progress_bar): m_dlbutton(dl_button), m_progress_bar(progress_bar)
{
}

void ResetWidgetCallback::operator()(VideoInfo* , std::string&)
{
    m_dlbutton -> Enable();
    m_progress_bar -> Destroy();
}
