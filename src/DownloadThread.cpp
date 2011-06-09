#include "DownloadThread.hpp"

DownloadThread::DownloadThread(VideoInfo* video_data) : wxThread() ,video_info(video_data)
{

}


void* DownloadThread::Entry()
{
    doDownload();
    return 0;
}


bool DownloadThread::doDownload()
 {

     std::cout << video_info -> getId().c_str() << std::endl;

     const char* file_name = video_info -> getLink().c_str();

	CURL* easyhandle = curl_easy_init();
        curl_easy_setopt( easyhandle, CURLOPT_URL, video_info -> getThumbnail().c_str() ) ;
        FILE* file = fopen(video_info -> getId().c_str(), "wb");
	if(file){
	    curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;
	    curl_easy_perform( easyhandle );
	    curl_easy_cleanup( easyhandle );
	    fclose(file); //make sure to close file
	}


}
