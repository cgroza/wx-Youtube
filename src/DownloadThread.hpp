#ifndef DOWNLOAD_THREAD_H
#define DOWNOLAD_THREAD_H

#include <wx/thread.h>
#include "VideoInfo.hpp"
#include <cstdlib>
#include <curl/curl.h>
#include <string>
#include <iostream>

class DownloadThread : public wxThread
{

public:
    DownloadThread(VideoInfo* video_data, const std::string& url, const std::string& path, 
		                                     void (*callback)(VideoInfo*, std::string&));

    virtual void* Entry();

protected:
    std::string m_url; //downolad url
    std::string m_path; //save path
    VideoInfo* m_video_data; //additional data required by callback function
    void (*p_callback)(VideoInfo*, std::string&); //called on tread end

private:

    bool doDownload();  //fetches the file
};


#endif
