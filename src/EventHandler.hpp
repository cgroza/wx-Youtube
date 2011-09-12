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
