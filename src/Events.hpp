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
