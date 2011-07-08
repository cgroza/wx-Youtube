#include "DownloadThread.hpp"

DownloadThread::DownloadThread(VideoInfo* video_data, const std::string& url, const std::string& path,
        DownloadCallback* callback ,  int (*progress_callback)(void*, double, double , double , double)) : 

    wxThread() , m_url(url), m_path(path), m_video_data(video_data), p_callback(callback),
    m_curl_progress_callback(progress_callback)
{

}


DownloadThread::~DownloadThread()
{
    if(p_callback)
    {
	delete p_callback;
	p_callback = 0;
    }
}

void* DownloadThread::Entry()
{
    doDownload();
    return 0;
}


bool DownloadThread::doDownload()
 {
     // std::cout << m_path << std::endl;

	CURL* easyhandle = curl_easy_init();
        curl_easy_setopt( easyhandle, CURLOPT_URL, m_url.c_str() ) ;
        FILE* file = fopen(m_path.c_str(), "wb");

	if(file){

	    if(m_curl_progress_callback)
	    {

	    	// Install the callback function
	    	curl_easy_setopt(easyhandle, CURLOPT_NOPROGRESS, 0);
	    	curl_easy_setopt(easyhandle, CURLOPT_PROGRESSFUNCTION, m_curl_progress_callback);

	    }
	    curl_easy_setopt(easyhandle, CURLOPT_VERBOSE, 1L);
	    curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;
	    curl_easy_perform( easyhandle );
	    curl_easy_cleanup( easyhandle );
    	    fclose(file); //make sure to close file
	    if(p_callback)  p_callback->operator()(m_video_data, m_path);
	}

	
}
