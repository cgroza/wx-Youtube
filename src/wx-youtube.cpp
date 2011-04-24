

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

std::vector<VideoInfo*>* deal_with_result() //Needed some help with this one
{
    using namespace rapidxml;
	request_information *page_information;
	page_information = new request_information;


    std::vector<char> xml_copy(buffer.begin(), buffer.end());
    xml_copy.push_back('\0');
    rapidxml::xml_document<> doc;
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);


    page_information->version = doc.first_node()->first_attribute("version")->value();
    page_information->encoding = doc.first_node()->first_attribute("encoding")->value();


    xml_node<>* cur_node = doc.first_node("feed")->first_node("entry"); //Setup our initial node

    //Below is a prototype for the list insertion. I cannot seem to figure out how to insert into the wxlist from here.

    std::vector<VideoInfo*> * videos = new std::vector<VideoInfo*>; //the videos we just found.

    while (cur_node != NULL)
	{
	//	std::cout << cur_node->first_node("title")->value() << std::endl; // Find the first title node and output the value

        videos -> push_back( new VideoInfo(cur_node -> first_node("title") -> value()) ); //creating video info object for each found video.
        cur_node = cur_node->next_sibling("entry"); // Iterate to the next entry sibling

	}

    std::cout << videos -> at(0) -> getName();

    return videos; //return the videos we just found. These are to be taken and added to the GUI list.
}



std::vector<VideoInfo*>* get_search_result(wxString& search)  //had help with this
{
    using boost::format;
    std::string search_url = str(format("http://gdata.youtube.com/feeds/api/videos?q=%s")  % search.mb_str()) ;

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
	   return deal_with_result();
	}
	else
	{
	    //Needs to be a popup message
	    std::cout << "Error [" << result << "] - " << errorBuffer << std::endl;
	    return 0;
	}
    }
}

#endif






