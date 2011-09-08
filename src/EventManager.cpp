#include "EventManager.hpp"

EventManager::EventManager() {}


void EventManager::BindEvent(VideoSelect func)
{
    select_listeners.push_back(func);
}

void EventManager::BindEvent(Search func)
{
    search_listeners.push_back(func);
}

void EventManager::BindEvent(DeleteVideos func)
{
    delete_listeners.push_back(func);
}


void EventManager::FireEvent(VideoSearchEvent* event) const
{
    std::vector<Search>::const_iterator it = search_listeners.begin();
    for(it; it < search_listeners.end(); ++it) (*it)->operator()(event);

}

void EventManager::FireEvent(VideoSelectEvent* event) const
{
    std::vector<VideoSelect>::const_iterator it = select_listeners.begin();
    for(it; it < select_listeners.end(); ++it) (*it)->operator()(event);

}

void EventManager::FireEvent(VideosDeleteEvent* event) const
{
    std::vector<DeleteVideos>::const_iterator it = delete_listeners.begin();
    for(it; it < delete_listeners.end(); ++it) (*it)->operator()(event);

}
