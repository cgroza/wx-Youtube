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

#include <iostream>
#include <vector>
#include <map>
#include <wx/wx.h>
#include <iostream>
#include <cstdlib>
#include "curl/curl.h"
#include <boost/format.hpp>
#include <boost/algorithm/string/split.hpp>
#include <sstream>
#include <string>
#include "rapidxml/rapidxml.hpp"

#ifndef EXTRACT_H
#define EXTRACT_H
	static std::map <std::string, std::string> urls;
	static std::vector<std::string> tmp;
	static std::vector<std::string> tmp_args;
	static std::vector<std::string> stream_map;
	static std::string key;
	static std::string value;
	static std::map<std::string, std::string> params;
	static std::string tmp_url;
	static std::string format;
	static std::string real_url;
	static std::vector<std::string> itag_map;
	static std::string itag_key;
	static std::string itag_value;
	static std::string resolve_buffer;

class Extract
{
    public:
	std::vector<std::string> formats;
	static std::string format_url(std::string id);
	static void resolve_real_url(std::string id);
	static void gather_formats();
	static std::string return_url(std::string format);
	static std::string return_ext(std::string url);
	static std::string encode_search(std::string search);
	
	struct video_struct
	{
	    std::string actual_url;
	    std::string id;
	    std::string best_ext;
	    std::string title;
	    std::string save_dir;
	    std::string extension;
	    std::string full_save_path;
	};
    protected:
	static int writer(char *data, size_t size, size_t nmemb, std::string *resolve_buffer);
};

#endif
