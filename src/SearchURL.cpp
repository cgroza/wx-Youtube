#include "SearchURL.hpp"


SearchURL::SearchURL(SearchType search_t, wxString& search_str)
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
    }

}

std::string SearchURL::getUrl() const
{
    return m_url;
}

const std::string SearchURL::VIDEO_SEARCH_URL = "http://gdata.youtube.com/feeds/api/videos?q=%s";
const std::string SearchURL::USER_VIDEO_SEARCH_URL = "http://gdata.youtube.com/feeds/api/users/%s/uploads";
