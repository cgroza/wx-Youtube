#include "VideoSearch.hpp"


VideoSearch::VideoSearch(const SearchURL* search_url): m_search_url(search_url), m_search_results(NULL)
{

}

//This is the writer call back function used by curl
int VideoSearch::writer(char *data, size_t size, size_t nmemb, std::string *buffer)
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

void VideoSearch::dealWithResult() //Needed some help with this one
{

    using namespace rapidxml;
	request_information *page_information;
	page_information = new request_information;


    std::vector<char> xml_copy(VideoSearch::buffer.begin(), VideoSearch::buffer.end());
    xml_copy.push_back('\0');
    rapidxml::xml_document<> doc;
    doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);

    //std::cout << doc << std::endl; //for debugging, usefull to have it.

    page_information->version = doc.first_node()->first_attribute("version")->value();
    page_information->encoding = doc.first_node()->first_attribute("encoding")->value();


    xml_node<>* cur_node = doc.first_node("feed")->first_node("entry"); //Setup our initial node

    std::vector<VideoInfo*> * videos = new std::vector<VideoInfo*>; //the videos we just found.


    while (cur_node != NULL)
	{

        videos -> push_back( new VideoInfo(cur_node -> first_node("title") -> value(),
          cur_node -> first_node("gd:rating")-> first_attribute("average") -> value(),
          cur_node -> first_node("yt:statistics")-> first_attribute("viewCount") -> value(),
          cur_node -> first_node("link") -> first_attribute("href") -> value(),
          cur_node-> first_node("media:group") -> first_node("media:description") -> value(),
          cur_node -> first_node("author") -> first_node("name") -> value(),
          cur_node -> first_node("id") -> value(),
          cur_node -> first_node("media:group") -> first_node("media:thumbnail") -> first_attribute("url") -> value())); //creating video info object for each found video.

        cur_node = cur_node->next_sibling("entry"); // Iterate to the next entry sibling

	}
    m_search_results = videos;
}



bool VideoSearch::doSearch()  //had help with this
{
    //using boost::format;
    //std::string search_url = str(format("http://gdata.youtube.com/feeds/api/videos?q=%s") % search.mb_str());

    CURL *curl;
    CURLcode result;

    //Create our curl handle
    buffer.clear();
    curl = curl_easy_init();

    if(curl)
    {
	//Now set up all of the curl options
	curl_easy_setopt(curl, CURLOPT_URL, m_search_url -> getUrl().c_str());
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &VideoSearch::writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &VideoSearch::buffer);

	//Attempt to retrive the remote page
	result = curl_easy_perform(curl);

	//Always cleanup
	curl_easy_cleanup(curl);

	switch(result)
	{
		case 0:
            m_curl_result = result;
            dealWithResult();
			return true;
        default:
            m_curl_result = result;
            return false;


        }
    }
}

std::vector<VideoInfo*>* VideoSearch::getSearchResults()
{
    return m_search_results;
}

int VideoSearch::getCurlCode() const
{
    return m_curl_result;
}

std::string VideoSearch::buffer = "";

