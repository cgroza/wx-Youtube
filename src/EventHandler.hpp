#ifndef EVENT_HANDLER_H
    #define EVENT_HANDLER_H
#include "Events.hpp"

class EventHandler
/*
  Every class that must handle an event must inherit from this class and
  implement the pure virtual functions.
 */
{
public:
    virtual void OnSearch(VideoSearchEvent& event) = 0;
    virtual void OnVideoSelect(VideoSelectEvent& event) = 0;
    virtual void OnDeleteVideos(VideosDeleteEvent& event) = 0;

};
#endif //EVENT_HANDLER_H
