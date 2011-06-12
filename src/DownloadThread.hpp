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
    DownloadThread(const std::string& url, const std::string& path);
    virtual void* Entry();

protected:
    std::string m_url;
    std::string m_path;

private:

    bool doDownload();
};


#endif
