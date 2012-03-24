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



#ifndef THUMB_NAIL_FRAME_H
    #define THUMB_NAIL_FRAME_H

#include "VideoInfo.hpp"
#include <string>
#include "ImageBox.hpp"


class ThumbnailFrame : public wxImageBox
{
public:
    ThumbnailFrame(wxWindow* parent, wxWindowID id = -1);
    void SetThumbnail(wxImage& image);
    void ProcessNewThumbnail(VideoInfo* video_data, std::string& path );
};

#endif // THUMBNAIL_FRAME_H
