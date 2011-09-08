#ifndef EVENT_MANAGER_H
    #define EVENT_MANAGER_H
#include "EventHandler.hpp"
#include "Events.hpp"
#include <vector>

class FunctionObject
{
public:
    virtual void operator()(EventBase* event){};
};

class SearchObjectFunction : public FunctionObject
{
public:
    virtual void operator()(VideoSearchEvent* event){};
};


class VideoSelectObjectFunction : public FunctionObject
{
public:
    virtual void operator()(VideoSelectEvent* event){};
};

class VideosDeleteObjectFunction : public FunctionObject
{
public:
    virtual void operator()(VideosDeleteEvent* event){};
};


class EventManager
/*
This class takes care of managing the function pointers called
upon firing an event.

*/


{
public:
    typedef SearchObjectFunction* Search;
    typedef VideoSelectObjectFunction* VideoSelect;
    typedef  VideosDeleteObjectFunction*  DeleteVideos;

    EventManager();
    /*
      This method binds an event which is fired upon selecting a
      video in the list.
     */
    void BindEvent(VideoSelect);

    /*
      This method binds an event which is fired upon searching
      videos.
     */
    void BindEvent(Search);
    /*
      This method binds an event which is fired upon
      clearing of the video list.
    */
    void BindEvent(DeleteVideos); 

    void FireEvent(VideoSearchEvent* event) const;
    void FireEvent(VideoSelectEvent* event) const;
    void FireEvent(VideosDeleteEvent* event) const;

protected:
    std::vector<Search> search_listeners;
    std::vector<VideoSelect> select_listeners;
    std::vector<DeleteVideos> delete_listeners;

};







#endif // EVENT_MANAGER_H
