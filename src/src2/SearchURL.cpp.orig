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



#include "SearchURL.hpp"
#include <iostream>



SearchURL::SearchURL(SearchType search_t, wxString& search_str, int start_index, int max_results) : m_search_type(search_t) 
{
    using boost::format;
    switch (search_t)
    {
        case VIDEO_SEARCH:
	    //% nr_videos.mb_str()
            m_url = (str(boost::format(VIDEO_SEARCH_URL) % search_str.mb_str() % max_results % start_index));
	    std::cout << m_url << std::endl;
            break;
        case USER_VIDEO_SEARCH:
            m_url = (str(boost::format(USER_VIDEO_SEARCH_URL) % search_str.mb_str() % max_results % start_index));
	    std::cout << m_url << std::endl;
            break;

        case PLAY_LIST_SEARCH:
	    m_url = (str(boost::format(PLAYLIST_SEARCH_URL) % search_str.mb_str() % max_results % start_index));
	    std::cout << m_url << std::endl;
	    break;

        case VIDEO_COMMENTS_SEARCH:
	    m_url = (str(boost::format(VIDEO_COMMENTS_SEARCH_URL) % search_str.mb_str()));
	    std::cout << m_url << std::endl;
	    break;

    }
    // replacing spaces with encoded space " " with -
    // if we do not do this, the search will fail.
    // youtube treats spaces and "-" the same way
    //boost::replace_all(m_url, " ","-");


}

std::string SearchURL::getUrl() const
{
    return m_url;
}

SearchType SearchURL::getSearchType () const
{
    return m_search_type;
}
// initialize the static URL strings
const std::string SearchURL::VIDEO_SEARCH_URL = "http://gdata.youtube.com/feeds/api/videos?q=%s&max-results=%s&start-index=%s";
const std::string SearchURL::USER_VIDEO_SEARCH_URL = "http://gdata.youtube.com/feeds/api/users/%s/uploads?max-results=%s&start-index=%s";
const std::string SearchURL::PLAYLIST_SEARCH_URL = "http://gdata.youtube.com/feeds/api/playlists/snippets?q=%s&max-results=%s&start-index=%s&v=2";
const std::string SearchURL::VIDEO_COMMENTS_SEARCH_URL = "http://gdata.youtube.com/feeds/api/videos/%s/comments";
