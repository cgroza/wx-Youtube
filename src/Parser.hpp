#ifndef PARSER_H
    #define PARSER_H

#include <vector>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "VideoInfo.hpp"

class Parser
{
public:
    // parses youtube playlist feed.
    static void parsePlaylistFeed(std::vector<VideoInfo*>* buffer, rapidxml::xml_document<>* feed);
    // parses the youtube video feed
    static void parseVideoFeed(std::vector<VideoInfo*>* buffer, rapidxml::xml_document<>* feed);
};

#endif	// PARSER_H
