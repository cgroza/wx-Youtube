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


class VideoSearch
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
    void dealWithResult();

//search URL used by the youtube API
    const SearchURL* m_search_url;
    int m_curl_result;
    std::vector<VideoInfo*>* m_search_results;


public:

    VideoSearch(const SearchURL* search_url);
    ~VideoSearch();

    // fetches the youtube xml feed
    bool doSearch();

    //returns search video info entries.
    std::vector<VideoInfo*>* getSearchResults();

    int getCurlCode() const;
};


#endif
