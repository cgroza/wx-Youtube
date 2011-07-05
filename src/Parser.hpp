#ifndef PARSER_H
    #define PARSER_H

#include <vector>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "VideoInfo.hpp"
#include "CommentInfo.hpp"


class Parser
{
public:
    // parses youtube playlist feed.
    static void parsePlaylistFeed(std::vector<VideoInfo*>* buffer, rapidxml::xml_document<>* feed);
    // parses the youtube video feed
    static void parseVideoFeed(std::vector<VideoInfo*>* buffer, rapidxml::xml_document<>* feed);
    // parses the youtube comments feed
    static void parseCommentsFeed(std::vector<CommentInfo*>* buffer, rapidxml::xml_document<>* feed);
};


#endif	// PARSER_H
