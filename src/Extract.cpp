#include <iostream>
#include <cstdlib>
#include "curl/curl.h"
#include <boost/format.hpp>
#include <sstream>
#include <string>
#include "urilite.h"
#include "Extract.hpp"

    

std::string Extract::resolve_buffer;
int start;

int Extract::writer(char *data, size_t size, size_t nmemb, std::string *resolve_buffer)
{
    //What we will return
    int result = 0;

    //Is there anything in the buffer?
    if (resolve_buffer != NULL)
    {
	//Append the data to the buffer
	resolve_buffer->append(data, size * nmemb);

	//How much did we write?
	result = size * nmemb;
    }
    return result;
}

std::string Extract::format_url(std::string id)

{
    
    std::string url;
    //using boost::format;
    //std::string search_url = str(format("http://gdata.youtube.com/feeds/api/videos?q=%s") % search.mb_str());
    //http://www.youtube.com/watch?v=WSeNSzJ2-Jw
    
    
    url = "http://www.youtube.com/get_video_info?&video_id=" + id;
    std::cout << "Formated url: " << url << std::endl;
    
    return url;
    
}


std::string Extract::extension()
{
    std::string format;
    start = resolve_buffer.find("fmt_url_map=");
    start = start + 12;
    
    
    switch (atoi(resolve_buffer.substr(start, 2).c_str()))
    {
	case 5 :  
	case 34: 
	case 35: 
	format = "flv"; 
	break;
	
	case 18:
	case 22:
	case 37:
	case 38:
	format = "mp4";
	break;
	
	case 17:
	format = "3gp";
	break;
	
	default: 
	format = "";
	break;
    }
    return format;	 
}
std::string Extract::resolve_real_url(std::string id)
{
    //This function connects to the internet, and retrieves the
    //real download url so we can pass it to our download function
    //AFAIK videos can only be downloaded once from the given url (each url has a unique signature), and can only be downloaded from that IP address.
    
    id = format_url(id);
    std::cout << "Resolving real url for " << id << std::endl;
    CURL *resolve;
    CURLcode result;
    resolve_buffer.clear();
    resolve = curl_easy_init();
    if(resolve)
    {
	//Curl options
	curl_easy_setopt(resolve, CURLOPT_URL, id.c_str());
	curl_easy_setopt(resolve, CURLOPT_HEADER, 0);
	curl_easy_setopt(resolve, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(resolve, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(resolve, CURLOPT_WRITEDATA, &resolve_buffer);
	
	//Attempt to retrive the remote page
	result = curl_easy_perform(resolve);

	//Always cleanup
	curl_easy_cleanup(resolve);
	
	//Did we succeed?
	if (result == CURLE_OK)
	{
	    //All the magic happens here
	    start = resolve_buffer.find("fmt_url_map=") + 17;
	    std::string q_string = resolve_buffer.substr(start, resolve_buffer.length());
	    std::string real_url = urilite::uri::decode2(q_string.substr(0, q_string.find("%2C")));
	    std::cout << "Download link found!" << std::endl;
	    return real_url;
	}
	else
	{
	    std::cout << "Error [" << result << "] - " << std::endl;
	    return "";
	}
    }
}




