#ifndef SEARCH_URL_H
#define SEARCH_URL_H

#include <boost/format.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <string>
#include <map>
#include "Enums.hpp"
#include <wx/wx.h>

class SearchURL
{

private:
     std::string m_url;
     // will be used to format a search url.
     static const std::string VIDEO_SEARCH_URL;
     static const std::string USER_VIDEO_SEARCH_URL;
     static const std::string PLAYLIST_SEARCH_URL;
     const SearchType m_search_type;

public:
    SearchURL(SearchType search_t, wxString& search_str);
    std::string getUrl() const; // returns the URL as a string
    SearchType getSearchType() const;//returns the search type
};
#endif
