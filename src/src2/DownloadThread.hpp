//Copyright (C) 2011  Groza Cristian, N3
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



#ifndef DOWNLOAD_THREAD_H
#define DOWNLOAD_THREAD_H

#include <wx/thread.h>
#include "VideoInfo.hpp"
#include <cstdlib>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include "DownloadCallback.hpp"


class DownloadThread : public wxThread
{

public:
    DownloadThread(VideoInfo* video_data, const std::string& url, const std::string& path, 
	   DownloadCallback* callback = 0, int (*progress_callback)(void*, double, double , double , double)=0);


    ~DownloadThread();
    virtual void* Entry();

protected:
    std::string m_url; //downolad url
    std::string m_path; //save path
    VideoInfo* m_video_data; //additional data required by callback function
    DownloadCallback* p_callback; //function object called on tread end
    int (*m_curl_progress_callback)(void*, double, double , double , double);

private:

    bool doDownload();  //fetches the file
};


#endif
