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



#ifndef EVENTS_H
    #define EVENTS_H

#include "VideoInfo.hpp"
#include <vector>



class EventBase
/*
All events must inherit from this class and implement the  virtual methods.
This class will be used as information transmitters for the listeners.
*/
{

};

class VideoSearchEvent : public EventBase
/*
This event represents a video search. It contains the std::vecotr<VideoInfo*> of results.

 */

{
public:
    VideoSearchEvent(std::vector<VideoInfo*>* search_results);
    std::vector<VideoInfo*>* GetResults() const;

private:
    std::vector<VideoInfo*>* m_results;
};


class VideoSelectEvent : public EventBase
/*
  This event represents a video selection. It contains the currently selected VideoInfo*
 */
{

public:
    
    VideoSelectEvent(VideoInfo* video_info);
    VideoInfo* GetVideoInfo() const;

private:
    VideoInfo* m_video_info;

};

class VideosDeleteEvent : EventBase
/* This event represents the total deletion of the displayed videos. It contains nothing. */
{
public:
    
private:
};

#endif // EVENTS_H
