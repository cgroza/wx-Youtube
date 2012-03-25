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
