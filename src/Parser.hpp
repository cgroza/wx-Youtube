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



#ifndef PARSER_H
    #define PARSER_H

#include <iostream>
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
