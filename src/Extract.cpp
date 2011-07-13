#include <iostream>
#include <cstdlib>
#include "curl/curl.h"
#include <boost/format.hpp>
#include <boost/algorithm/string/split.hpp>
#include <sstream>
#include <string>
#include "urilite.h"
#include "Extract.hpp"

    

std::string Extract::resolve_buffer;
std::vector<std::string> Extract::formats;
std::string Extract::mp4_url;
std::string Extract::flv_url;
std::string Extract::three_gp_url;


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





void Extract::gather_formats()
{
    //This function goes through the retrieved url and grabs all the formats available.
    using namespace boost;
    std::string format;
    std::cout << "[#]Gathering formats" << std::endl;
    //First we need index the location of "fmt_url_map" and save it to a var.
    start = resolve_buffer.find("fmt_url_map=");
    start = start + 12;
    
    //Here we initilize a vector, decode the buffer, and seperate the relative string.
    std::vector<std::string> tmp;
    std::string fmt_map = urilite::uri::decode2(resolve_buffer.substr(start, resolve_buffer.length()).c_str());
    
    //I used boost to split this, similar to Python
    split(tmp, fmt_map, is_any_of(","));
    
    //For each "," we will run our validation checks and attempt to grab a url, if successful, it will be "push_back" into the vector.
    for (int num = 0; num < tmp.size(); num++)
    {
	std::string tmp_str = tmp[num].substr(0,3);  //We only need to check the first three characters
	
	if (tmp_str.find("|") == std::string::npos)  //If "|" cannot be found, then it is invalid
	{
	    continue;
	}
	    
	else //If a valid format/url is found, we will continue to process it.
	{
	    std::string real_url = tmp[num].substr(tmp[num].find_first_of("h"), tmp[num].length());
	    
	    
	    real_url = real_url.substr(0, real_url.find("|"));
	    
	    real_url = real_url.substr(0, real_url.find(",")); 
	    
	    {
		
		switch (atoi(tmp_str.c_str())) 		     //Turns the str into a int, so we can use "switch"
		{
		    case 5 :  
		    case 34: 
		    case 35: 
		    formats.push_back("flv"); 	
		    flv_url = real_url;
		    break;

		    case 18:
		    case 22:
		    case 37:
		    case 38:
		    formats.push_back("mp4");
		    mp4_url = real_url;
		    break;
	
		    case 17:
		    formats.push_back("3gp");
		    three_gp_url = real_url;
		    break;
	
		    default: 
		    break;
		
		}	
	    }
	}
    }
}


std::string Extract::extension()
{
    //Here we return the best format, it goes in order, returning the first one found.
    
    //gather_formats();
    
    if (mp4_url != "") { return "mp4"; }
    if (flv_url != "") { return "flv"; }
    if (three_gp_url != "") { return "3gp"; }
	
    
    
    return "";
}

std::string Extract::return_url()
{
    gather_formats();
    //extension();
    std::string best = "[#]Best format: ";
    std::cout << "[#]Finding highest quality" << std::endl;
    
    if (mp4_url != "") { std::cout << best + "mp4" << std::endl; return mp4_url; }
    if (flv_url != "") { std::cout << best + "flv" << std::endl; return flv_url; }
    if (three_gp_url != "") { std::cout << best + "3gp" << std::endl; return three_gp_url; }
	
    
    
    return "";
}

std::string Extract::resolve_real_url(std::string id)
{
    //This function connects to the internet, and retrieves the
    //real download url so we can pass it to our download function
    //AFAIK videos can only be downloaded once from the given url (each url has a unique signature), and can only be downloaded from that IP address.
    
    id = format_url(id);
    std::cout << "[#]Resolving real url for " << id << std::endl;
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
	    
	    //std::string q_string = resolve_buffer.substr(start, resolve_buffer.length());
	    //std::string real_url = urilite::uri::decode2(q_string.substr(0, q_string.find("%2C")));
	    //std::cout << "Download link found!" << std::endl;
	    
	    return return_url();
	}
	else
	{
	    std::cout << "Error [" << result << "] - " << std::endl;
	    return "";
	}
    }
}




