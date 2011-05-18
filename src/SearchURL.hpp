#ifndef SEARCH_URL_H
#define SEARCH_URL_H

#include <boost/format.hpp>
#include <string>
#include <map>
#include "Enums.hpp"
#include <wx/wx.h>

class SearchURL
{

private:
     std::string m_url;

     static const std::string VIDEO_SEARCH_URL;


public:
    SearchURL(SearchType search_t, wxString& search_str);
    std::string getUrl() const;

};
#endif
