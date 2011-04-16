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
#include "curl/curl.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

//All the interent shit

//Write any errors in here
static char errorBuffer[CURL_ERROR_SIZE];

//Write all expected data in here
static std::string buffer;


//This is the writer call back function used by curl
static int writer(char *data, size_t size, size_t nmemb, std::string *buffer);

void deal_with_result();


void get_search_result(wxString search);

#endif
