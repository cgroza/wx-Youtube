#ifndef VIDEO_SEARCH_H
#define VIDEO_SEARCH_H

#include <wx/wx.h>
#include <cstdlib>
#include <string>
#include <vector>
#include "curl/curl.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "VideoInfo.hpp"
#include "SearchURL.hpp"
#include "Parser.hpp"


class XMLFeed
{
private:
    struct request_information
    {
	std::string encoding;
	std::string version;
    };

//Write all expected data in here
    static std::string buffer;

//This is the writer callback function called by curl
    static int writer(char *data, size_t size, size_t nmemb, std::string *buffer);

//creates the video info vector
    bool parseFeed();

//search URL used by the youtube API
    const SearchURL* m_search_url;
    int m_curl_result;
    rapidxml::xml_document<>*  m_xml_feed;


public:

    XMLFeed(const SearchURL* search_url);
    ~XMLFeed();

    // fetches the youtube xml feed
    bool fetchFeed();

    //returns search video info entries.
    rapidxml::xml_document<>* getXMLFeed() const;

    int getCurlCode() const;
};


#endif
