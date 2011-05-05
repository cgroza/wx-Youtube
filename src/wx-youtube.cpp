

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

    std::vector<VideoInfo*> * videos = new std::vector<VideoInfo*>; //the videos we just found.

    //BUG : I do not know why, but this function always returns the results of the first search.
    //Example: I search skate, the results for skate show up. Next, I search Linux, the results for skate show up!!!!

    while (cur_node != NULL)
	{

        videos -> push_back( new VideoInfo(cur_node -> first_node("title") -> value(),
          cur_node -> first_node("gd:rating")-> first_attribute("average") -> value(),
          cur_node -> first_node("yt:statistics")-> first_attribute("viewCount") -> value(),
          "None",
          cur_node-> first_node("media:group") -> first_node("media:description") -> value(),
          cur_node -> first_node("author") -> first_node("name") -> value()) ); //creating video info object for each found video.

        cur_node = cur_node->next_sibling("entry"); // Iterate to the next entry sibling

	}


    return videos; //return the videos we just found. These are to be taken and added to the GUI list.
}



std::vector<VideoInfo*>* get_search_result(wxString& search)  //had help with this
{
    using boost::format;
    std::string search_url = str(format("http://gdata.youtube.com/feeds/api/videos?q=%s") % search.mb_str()) ;

    CURL *curl;
    CURLcode result;

    //Create our curl handle
    buffer.clear();
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
	   return deal_with_result(); //returns the videos collected by deal_with_result()
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
