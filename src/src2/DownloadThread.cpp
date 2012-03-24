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
    // set up curl
    CURL* easyhandle = curl_easy_init();
    curl_easy_setopt( easyhandle, CURLOPT_URL, m_url.c_str() ) ;
    FILE* file = fopen(m_path.c_str(), "wb");


    if(file)
    {
        if(m_curl_progress_callback)
        {

            // Install the callback function
            curl_easy_setopt(easyhandle, CURLOPT_NOPROGRESS, 0);
            curl_easy_setopt(easyhandle, CURLOPT_PROGRESSFUNCTION, m_curl_progress_callback);

        }
        curl_easy_setopt(easyhandle, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;
        curl_easy_setopt(easyhandle, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_perform( easyhandle );
        curl_easy_cleanup( easyhandle );
        fclose(file); //make sure to close file
        if(p_callback)  p_callback->operator()(m_video_data, m_path);
    }
}
