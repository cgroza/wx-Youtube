#ifndef DOWNLOAD_THREAD_H
#define DOWNOLAD_THREAD_H

#include <wx/thread.h>
#include "VideoInfo.hpp"
#include <cstdlib>
#include <curl/curl.h>
#include <iostream>

class DownloadThread : public wxThread
{

public:
    DownloadThread(VideoInfo* video_data);
    virtual void* Entry();
private:
    VideoInfo* video_info;
    bool doDownload();
};


#endif
