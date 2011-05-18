#include "SearchURL.hpp"


SearchURL::SearchURL(SearchType search_t, wxString& search_str)
{
    using boost::format;
    m_url = (str(format(VIDEO_SEARCH_URL) % search_str.mb_str()));

}

std::string SearchURL::getUrl() const
{
    return m_url;
}

const std::string SearchURL::VIDEO_SEARCH_URL = "http://gdata.youtube.com/feeds/api/videos?q=%s";
