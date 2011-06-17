#include <iostream>
#include <cstdlib>
#include <vector>
#include "curl/curl.h"
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <sstream>
#include <string>
#include "urilite.h"







static std::string buffer;


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

std::string return_url()

{
    //Static url
    std::string url;
    url = "http://www.youtube.com/get_video_info?&video_id=9boD5WIUGTw";
    return url;
    
}


std::string get_result()

{
    //fmt_url_map=37
    //http://www.youtube.com/get_video?video_id=video_id&t=token&fmt=18
    //http://v12.lscache5.c.youtube.com/
    
    int start;
    int end;
    std::string format;
    std::string token;
    std::string video_id;
    std::string test;
    std::string q_string;
    
    
    start = buffer.find("fmt_url_map=");
    start = start + 12;
    
    format = buffer.substr(start, 2);
    
    start = buffer.find("&token=");
    start = start + 7;
    end = buffer.find("&thumbnail_url=") - start;
    
    token = buffer.substr(start, end);
    
    //start = buffer.find("video_id=");
    //start = start + 9;
    
    //end = buffer.find("&length_seconds=") - start;
    
    //video_id = buffer.substr(start, end);
    
    
    
    start = buffer.find("fmt_url_map=") + 17;
    
    
    
    q_string = buffer.substr(start, buffer.length());
    
    std::string real_url = urilite::uri::decode2(q_string.substr(0, q_string.find("%2C")));
    
    
    
    
    //std::cout << real_url << std::endl;
    
     
    std::cout << "Token: "  << token  << std::endl;
    std::cout << "Format: " << format << std::endl;
    std::cout << "Video ID: " << video_id << std::endl;
    std::cout << "Url: " << real_url << std::endl; 
    
    return buffer;
    
}



std::string request()
{



	std::cout << "Retrieving " << std::endl;

	//Our curl objects
	CURL *curl;
	CURLcode result;
	
	buffer.clear();
	
	//Create our curl handle
	curl = curl_easy_init();

	if(curl)
	{
	    std::string search = return_url();
		
	    //Now set up all of the curl options
	    curl_easy_setopt(curl, CURLOPT_URL, search.c_str());
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
		//std::cout << "Getting result\n";
		get_result();
		exit(0);
	    }
	    else
	    {
		std::cout << "Error [" << result << "] - " << std::endl;
		exit(-1);

	    }
	}
    }


int main()
{
    request();
}
