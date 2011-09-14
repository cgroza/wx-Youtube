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



#ifndef SEARCH_URL_H
#define SEARCH_URL_H

#include <boost/format.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <string>
#include <map>
#include "Enums.hpp"
#include <wx/string.h>

class SearchURL
{

private:
    std::string m_url;
     // will be used to format a search url.
    static const std::string VIDEO_SEARCH_URL;
    static const std::string USER_VIDEO_SEARCH_URL;
    static const std::string PLAYLIST_SEARCH_URL;
    static const std::string VIDEO_COMMENTS_SEARCH_URL;

    const SearchType m_search_type;

public:
    SearchURL(SearchType search_t, wxString& search_str, const wxString& nr_videos = wxString("50", wxConvUTF8));
    std::string getUrl() const; // returns the URL as a string
    SearchType getSearchType() const;//returns the search type
};
#endif
