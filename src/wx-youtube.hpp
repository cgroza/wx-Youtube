//      Youtube-wx
//      Copyright 2011 Stealth. <stealth@ubuntu>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#ifndef WXYOUTUBE_H
#define WXYOUTUBE_H

#include <wx/wx.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <boost/format.hpp>
#include "curl/curl.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "VideoInfo.hpp"


struct request_information
{
	std::string encoding;
	std::string version;
};



//Write all expected data in here
static std::string buffer;


//This is the writer call back function used by curl
static int writer(char *data, size_t size, size_t nmemb, std::string *buffer);

std::vector<VideoInfo*>* deal_with_result();


std::vector<VideoInfo*>* get_search_result(wxString& search);

#endif
