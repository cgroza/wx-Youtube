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
    return "http://www.youtube.com/get_video_info?&video_id=" + id;
}





void Extract::gather_formats()
{
    //This function goes through the retrieved url and grabs all the formats available.
    
    std::cout << "[#]Gathering formats" << std::endl;
    
    using namespace boost;
    std::string format;
    std::string real_url;
    std::string key;
    std::string value;
    std::string tmp_url;
    std::map<std::string, std::string> params;
    
    std::vector<std::string> tmp;
    std::vector<std::string> tmp_args;
    std::vector<std::string> stream_map;
    std::string fmt_map = resolve_buffer;
    
    std::cout << "Complete response decoded: " << fmt_map << std::endl;
    split(tmp, fmt_map, is_any_of("|"));
    
    //http://v18.lscache1.c.youtube.com/videoplayback?sparams=id%2Cexpire%2Cip%2Cipbits%2Citag%2Calgorithm%2Cburst%2Cfactor&algorithm=throttle-factor&itag=18&ip=71.0.0.0&burst=40&sver=3&signature=5D682A1DA6D6153D39EC8F410C4F85DEE6C701E3.60FC504071DCCC39E736C21ADC6987B65B5B2FC9&expire=1311080400&key=yt1&ipbits=8&factor=1.25&id=feb0e649666337ae,5
    
    
    
    
    for (int i = 0; i < tmp.size(); i++)
    {
	
	
	
	split(tmp_args, tmp[i], is_any_of("&"));
	
	for (int a = 0; a < tmp_args.size(); a++)
	{
	    if (tmp_args[a].find("=") == std::string::npos) { continue; }
	    
	    key = urilite::uri::decode2(tmp_args[a].substr(0, tmp_args[a].find("=", 1)).c_str());
	    value =  urilite::uri::decode2(tmp_args[a].substr(tmp_args[a].find("=", 1)+1, tmp_args[a].length()).c_str());
	    
	    params[key] = value;
	   
	    std::cout << "[" << key << "]" << " = " << value << std::endl;
	
	
	}
	
	if (params.find("errorcode") != params.end())
	{ 
	    wxString errorcode_reason(params["reason"].c_str(), wxConvUTF8); //This needs to be displayed
	    wxMessageBox(errorcode_reason, wxT("Error"), wxOK | wxICON_ERROR ); 
	}
	
	
	//real_url = tmp[i].substr(0, tmp[i].find(","));
	
	
	
	
	if (params.find("url_encoded_fmt_stream_map") != params.end())
	{
	    split(stream_map, params["url_encoded_fmt_stream_map"], is_any_of("&"));
	    
	    for (int s = 0; s < stream_map.size(); s++)
	    {
		
		if (urilite::uri::decode2(stream_map[s].substr(0, stream_map[s].find("=", 1)).c_str()) == "itag")
		{
		    
		    tmp_url = urilite::uri::decode2(stream_map[s].substr(stream_map[s].find("=", 1)+1, stream_map[s].length()).c_str());
		    if (tmp_url.find("url=") == std::string::npos) { continue; }
		    
		    //18,url
		    format = tmp_url.substr(0, tmp_url.find(",",1));
		    real_url = tmp_url.substr(tmp_url.find("url=",1)+4, tmp_url.length());
		    
		    
		    
		    //std::cout << "FORMAT: " << format << std::endl;
		    //std::cout << "REAL_URL: " << real_url << std::endl;
		    
		    switch (atoi(format.c_str()))
		    {
			case 5 :
			urls[format] = real_url;
			break;
			
			case 34:
			urls[format] = real_url;
			break;
			
			case 35: 
			urls[format] = real_url;	
			break;
		    
			case 18:
			urls[format] = real_url;
			break;
	    
			case 22:
			urls[format] = real_url;
			break;
	    
			case 37:
			urls[format] = real_url;
			break;
	    
			case 38:
			urls[format] = real_url;
			break;
	
			case 17:
			urls[format] = real_url;
			break;
	
			default: 
			break;
			
		    }	
		}
	    }
	}
		
	
	
	
	else
	{
		std::cout << "Could not find the stream map" << std::endl;
	}
	
	
	
	
	
    }
    std::cout << "Formats gathered" << std::endl;
}

std::string Extract::return_ext(std::string format)
{
    
    
    if (format != "best")
    {
	switch (atoi(format.c_str()))
	{
	    case 38: return "mp4";
	    case 37: return "mp4";
	    case 22: return "mp4";
	    case 18: return "mp4";
	
	    case 35: return "flv";
	    case 34: return "flv";
	    case 5:  return "flv";
	
	    case 17: return "3gp";
	    default: return "";
	}
    }
    

    
    if (urls["38"] != "") { return "mp4"; }
    if (urls["37"] != "") { return "mp4"; }
    if (urls["22"] != "") { return "mp4"; }
    if (urls["18"] != "") { return "mp4"; }
    
    if (urls["35"] != "") { return "flv"; }
    if (urls["34"] != "") { return "flv"; }
    if (urls["5"]  != "") { return "flv";  }
    
    if (urls["17"] != "") { return "3gp"; }
    
    
    return "";
}



std::string Extract::return_url(std::string format)
{
    
    
    if (format != "best") { return urls[format]; }
    
    
    if (urls["38"] != "") { return urls["38"]; }
    if (urls["37"] != "") { return urls["37"]; }
    if (urls["22"] != "") { return urls["22"]; }
    if (urls["18"] != "") { return urls["18"]; }
    
    if (urls["35"] != "") { return urls["35"]; }
    if (urls["34"] != "") { return urls["34"]; }
    if (urls["5"]  != "") { return urls["5"];  }
    
    if (urls["17"] != "") { return urls["17"]; }
    
    
    return "";
    
}


void Extract::resolve_real_url(std::string id)
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
	if (!result == CURLE_OK)
	{
	    std::cout << "Error [" << result << "] - " << std::endl;
	}
    }
    gather_formats();
}




