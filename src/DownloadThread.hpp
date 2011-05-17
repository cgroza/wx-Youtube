#ifndef DOWNLOAD_THREAD_H
#define DOWNOLAD_THREAD_H

#include <wx/wx.h>
#include "VideoInfo.hpp"

class DownloadThread : public wxThread
{

public:
    DownloadThread(VideoInfo* video_data);

private:
    VideoInfo* video_info;

};


#endif
