#include "DownloadThread.hpp"

DownloadThread::DownloadThread(VideoInfo* video_data, const std::string& url, const std::string& path,
			       DownloadCallback* callback ) : 
    wxThread() , m_url(url), m_path(path), m_video_data(video_data), p_callback(callback)
{

}


DownloadThread::~DownloadThread()
{
    delete p_callback;
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
	    curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;
	    curl_easy_perform( easyhandle );
	    curl_easy_cleanup( easyhandle );
	    fclose(file); //make sure to close file
	    if(p_callback)  p_callback->operator()(m_video_data, m_path);
	}

	
}
