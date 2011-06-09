#include "SearchURL.hpp"
#include <iostream>



SearchURL::SearchURL(SearchType search_t, wxString& search_str) : m_search_type(search_t) 
{
    using boost::format;
    switch (search_t)
    {
        case VIDEO_SEARCH:
            m_url = (str(format(VIDEO_SEARCH_URL) % search_str.mb_str()));
            break;
        case USER_VIDEO_SEARCH:
            m_url = (str(format(USER_VIDEO_SEARCH_URL) % search_str.mb_str()));
            break;

        case PLAY_LIST_SEARCH:
	    m_url = (str(format(PLAYLIST_SEARCH_URL) % search_str.mb_str()));
	    break;
    }
    // replacing spaces with encoded space " " with -
    // if we do not do this, the search will fail.
    // youtube treats spaces and "-" the same way
    boost::replace_all(m_url, " ","-");


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
const std::string SearchURL::VIDEO_SEARCH_URL = "http://gdata.youtube.com/feeds/api/videos?q=%s";
const std::string SearchURL::USER_VIDEO_SEARCH_URL = "http://gdata.youtube.com/feeds/api/users/%s/uploads";
const std::string SearchURL::PLAYLIST_SEARCH_URL = "http://gdata.youtube.com/feeds/api/playlists/snippets?q=%s&v=2";
