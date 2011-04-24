
#include <iostream>
#include <cstdlib>
#include <vector>
#include "curl/curl.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

//Write any errors in here
static char errorBuffer[CURL_ERROR_SIZE];

//Write all expected data in here
static std::string buffer;

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

void usage()
{
    std::cout << "curltest: \n" << std::endl;
    std::cout << "Usage: curltest url\n" << std::endl;
}

void get_result() //Needed some help with this one
{
    
    vector<char> xml_copy(buffer.begin(), buffer.end());
    xml_copy.push_back('\0');
    xml_document<> doc;
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);
    
    std::string version = doc.first_node()->first_attribute("version")->value();
    std::string encoding = doc.first_node()->first_attribute("encoding")->value();
    
    xml_node<>* cur_node = doc.first_node("feed")->first_node("entry");
   
    
    while (cur_node != NULL)
	{
		std::cout << cur_node->first_node("title")->value() << std::endl;
		cur_node = cur_node->next_sibling("entry");
	}
		

int main(int argc, char* argv[])
{
    
    
    if (argc > 1)
    {
	std::string url(argv[1]);
	
	std::cout << "Retrieving " << url << std::endl;
	
	//Our curl objects 
	CURL *curl;
	CURLcode result;
	
	//Create our curl handle
	curl = curl_easy_init();
	
	if(curl)
	{
	    //Now set up all of the curl options
	    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer); 
	    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);  
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
		get_result();
		exit(0);
	    }
	    else
	    {
		cout << "Error [" << result << "] - " << errorBuffer << endl;
		exit(-1);
		
	    }
	}
    }
}


