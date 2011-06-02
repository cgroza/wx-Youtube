//Prototype to iterate through the user videos

#include <iostream>
#include <cstdlib>
#include <vector>
#include "curl/curl.h"
#include <boost/format.hpp>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include <sstream>
#include <string>



using namespace std;
using namespace rapidxml;
using namespace boost;

static std::string buffer;
void get_result(int &page_num);


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



std::string return_url(int &page_num)
{
    
	//I've learned from youtube-dl that (I tried to acutally implement it for youtube-dl, but somebody else beat me to it) you need to update the start-index by 25 everytime you go back for more.
	//So thats what I've implemented here. 
	//http://gdata.youtube.com/feeds/api/videos?start-index=25&q=example
	//I'll make this a preference option for the "search videos" option.
	
	using boost::format;
	std::cout << "Start index is: " << page_num << std::endl;
	int temp = page_num * 25; //Make temp the result we need
	std::cout << "Converted index is: " << temp << std::endl;
	std::string search = "example";
	std::string search_url = str(format("http://gdata.youtube.com/feeds/api/videos?start-index=%s&q=%s") % temp % search);
	return search_url;
}





std::string request(int &page_num)
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
		std::string search = return_url(page_num);
		
		
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
		cout << "Getting result\n";
		get_result(page_num);
		exit(0);
	    }
	    else
	    {
		cout << "Error [" << result << "] - " << std::endl;
		exit(-1);

	    }
	}
    }




void get_result(int &page_num) 
{

    vector<char> xml_copy(buffer.begin(), buffer.end());
    xml_copy.push_back('\0');
    xml_document<> doc;
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

    std::string version = doc.first_node()->first_attribute("version")->value();
    std::string encoding = doc.first_node()->first_attribute("encoding")->value();

    xml_node<>* cur_node = doc.first_node("feed")->first_node("entry");


	
	int counter = 1;
			
	while (cur_node != NULL)
	{
		counter++;
		std::cout << cur_node->first_node("title")->value() << std::endl;
		cur_node = cur_node->next_sibling("entry");
		
		if (counter == 25)
		{
		    
			page_num++;
			std::cout << "page_num is at" << page_num << std::endl;
			std::cout << "Counter is at: " << counter << std::endl;
			
			request(page_num);
		}
	}
} 	













int main() 
{ 
    int page_num = 1;
    request(page_num); 
    return 0;
}
