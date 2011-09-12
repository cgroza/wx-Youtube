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



#ifndef VIDEOLISTCTRL_H
#define VIDEOLISTCTRL_H
#include <wx/wx.h>
#include <string>
#include <vector>
#include "VideoEntry.hpp"
#include "Enums.hpp"
#include "VideoInfo.hpp"


class VideoListCtrl: public wxListView {

/* This class was created to facilitate video entries management easier.
 * Feel free to add any method that you may think it will make things easier.
 */

public:
    /*Basic constructor.*/
    VideoListCtrl(wxWindow* parent);

    /*This method creates a wxListItem and sets its arguments as labels. */
    void AddVideo(VideoInfo* video_data);

    VideoEntry* GetVideoEntry(long index);
    bool DeleteAllItems();
private:


    std::vector<VideoEntry*> entries;

    wxListItem itemTitle;  //title column
    wxListItem itemRating; //rating column
    wxListItem itemViews;
    wxListItem itemAuthor;


protected:

};


#endif
