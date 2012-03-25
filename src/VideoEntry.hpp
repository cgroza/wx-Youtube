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

#ifndef VIDEOENTRY_H
#define VIDEOENTRY_H

#include <wx/wx.h>
#include "VideoInfo.hpp"

class VideoEntry : public  wxListItem{
public:
    /*Basic constructor.*/
    VideoEntry(VideoInfo* video_data);

    /*Video data getter function. */
    virtual VideoInfo* getVideoData();

    /*Video data setter function.*/
    virtual void setVideoData(VideoInfo* video_data);
private:
    VideoInfo* video;
};

#endif
