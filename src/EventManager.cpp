#include "EventManager.hpp"

EventManager::EventManager() {}


void EventManager::BindSelectVideoEvent(VideoSelect func)
{
    select_listeners.push_back(func);
}

void EventManager::BindSearchEvent(Search func)
{
    search_listeners.push_back(func);
}

void EventManager::BindDeleteVideosEvent(DeleteVideos func)
{
    delete_listeners.push_back(func);
}


void EventManager::FireVideoSearchEvent(VideoSearchEvent* event) const
{
    std::vector<Search>::const_iterator it = search_listeners.begin();
    for(it; it < search_listeners.end(); ++it) (*it)->operator()(event);

}

void EventManager::FireVideoSelectEvent(VideoSelectEvent* event) const
{
    std::vector<VideoSelect>::const_iterator it = select_listeners.begin();
    for(it; it < select_listeners.end(); ++it) (*it)->operator()(event);

}

void EventManager::FireVideosDeleteEvent(VideosDeleteEvent* event) const
{
    std::vector<DeleteVideos>::const_iterator it = delete_listeners.begin();
    for(it; it < delete_listeners.end(); ++it) (*it)->operator()(event);

}
