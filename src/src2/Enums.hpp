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



#ifndef ENUMS_H
#define ENUMS_H


enum
{
    TEXT_Search =  1,
    TEXT_num_vids,
    MENU_Quit  ,
    MENU_About,
    MENU_Pref,
    BUTTON_Go,
    BUTTON_Download,
    ID_COMBOBOX,
    LIST_Video_list,
    ID_RADIOBUTTON1,
};

enum SearchType
{
    VIDEO_SEARCH,
    USER_VIDEO_SEARCH,
    PLAY_LIST_SEARCH,
    VIDEO_COMMENTS_SEARCH
};


enum
{
    NO_SEARCH_RESULT=1000

};
#endif


