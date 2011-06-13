#ifndef DOWNLOAD_CALLBACK_H
    #define DOWNLOAD_CALLBACK_H
#include "VideoInfo.hpp"
#include "ThumbnailFrame.hpp"
#include <string>

class DownloadCallback
{
public:

    virtual void operator()(VideoInfo* video_data, std::string& path);

};



class ThumbnailDownloadCallback: public DownloadCallback
{
public:
    ThumbnailDownloadCallback(ThumbnailFrame* thumb_obj);
    virtual void operator()(VideoInfo* video_data, std::string& path);
private:
    ThumbnailFrame* m_thumb_obj;
};
#endif	// DOWNLOAD_CALLBACK_H
