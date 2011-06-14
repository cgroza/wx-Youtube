#include <iostream>
#include <cstdlib>
#include <vector>
#include "curl/curl.h"
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <sstream>
#include <string>





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
    url = "http://www.youtube.com/get_video_info?&video_id=9boD5WIUGTw&el=detailpage&ps=default&eurl=&gl=US&hl=en";
    return url;
    
}

std::string get_result()

{
    //fmt_url_map=37
    //^  --match the beggining of a line
    //?  --match the preceding expression zero or one time
    //
    
    int start;
    int end;
    start = buffer.find("fmt_url_map=");
    end = start - start+14;
    
    std::cout << buffer.substr(start, end) << std::endl;
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
		std::cout << "Getting result\n";
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
