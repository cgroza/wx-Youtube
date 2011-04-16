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



#include "wx-youtube.hpp"

#ifdef WXYOUTUBE_H

//This is the writer call back function used by curl
static int writer(char *data, size_t size, size_t nmemb, std::string *buffer)
{
    //What we will return
    int result = 0;

    //Is there anything in the buffer?
    if (buffer != NULL)
    {
	//Append the data to the buffer
	buffer->append(data, size * nmemb);

	//How much did we write?
	result = size * nmemb;
    }
    return result;
}

void deal_with_result() //Needed some help with this one
{
    std::vector<char> xml_copy(buffer.begin(), buffer.end());
    xml_copy.push_back('\0');
    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_full>(&xml_copy[0]);
    std::string version = doc.first_node()->first_attribute("version")->value();
    std::string encoding = doc.first_node()->first_attribute("encoding")->value();
    //std::cout << "Result " << doc << endl << "Version: " << version << endl << "Encoding " << encoding << endl;
}



void get_search_result(wxString search)  //had help with this
{
    std::string converted = std::string(search.mb_str());
    std::string search_url = std::string("http://gdata.youtube.com/feeds/api/videos?q=" +converted) ;

    CURL *curl;
    CURLcode result;

    //Create our curl handle
    curl = curl_easy_init();

    if(curl)
    {
	//Now set up all of the curl options
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
	curl_easy_setopt(curl, CURLOPT_URL, search_url.c_str());
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

	//Attempt to retrive the remote page
	result = curl_easy_perform(curl);

	//Always cleanup
	curl_easy_cleanup(curl);


	//Did we succeed?
	if (result == CURLE_OK)
	{
	    deal_with_result();
	}
	else
	{
	    //Needs to be a popup message
	    std::cout << "Error [" << result << "] - " << errorBuffer << std::endl;
	    exit(-1);
	}
    }
}

#endif






