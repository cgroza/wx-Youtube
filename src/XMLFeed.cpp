#include "XMLFeed.hpp"
using namespace rapidxml;

XMLFeed::XMLFeed(const SearchURL* search_url): m_search_url(search_url), m_xml_feed(0)
{
    m_xml_feed = new rapidxml::xml_document<>();
}

XMLFeed::~XMLFeed()
{
    delete m_xml_feed;
}

//This is the writer call back function used by curl
int XMLFeed::writer(char *data, size_t size, size_t nmemb, std::string *buffer)
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

void XMLFeed::parseFeed() //Needed some help with this one
{   
    // request_information *page_information;
    // page_information = new request_information;


//    std::vector<char> xml_copy(XMLFeed::buffer.begin(), XMLFeed::buffer.end());
//    xml_copy.push_back('\0');



    try{                        // in the case of an invalid xml document sent by curl
                                // an invalid user search may throw an exception
	m_xml_feed -> parse<parse_declaration_node | parse_no_data_nodes>(&XMLFeed::buffer[0]);
    }
    catch(rapidxml::parse_error e) {

      std::cout << "Could not parse youtube xml feed!";
      return;
    }


    // page_information->version = m_xml_feed -> first_node()->first_attribute("version")->value();
    // page_information->encoding = m_xml_feed -> first_node()->first_attribute("encoding")->value();

    

}



bool XMLFeed::fetchFeed()
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
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &XMLFeed::writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &XMLFeed::buffer);

        //Attempt to retrive the remote page
        result = curl_easy_perform(curl);

        //Always cleanup
        curl_easy_cleanup(curl);

        switch(result)
        {
        case 0:
            m_curl_result = result;
            parseFeed();
            return true;
        default:
            m_curl_result = result;
            return false;


        }
    }
}

rapidxml::xml_document<>* XMLFeed::getXMLFeed() const
{

    return m_xml_feed;
}

int XMLFeed::getCurlCode() const
{
    return m_curl_result;
}

// initializing static strings
std::string XMLFeed::buffer = "";

