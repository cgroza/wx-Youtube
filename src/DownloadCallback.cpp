#include "DownloadCallback.hpp"


void DownloadCallback::operator()(VideoInfo* video_data, std::string& path){}

ThumbnailDownloadCallback::ThumbnailDownloadCallback(ThumbnailFrame* thumb_obj): m_thumb_obj(thumb_obj)
{

}

void ThumbnailDownloadCallback::operator()(VideoInfo* video_data, std::string& path)
{

    m_thumb_obj -> ProcessNewThumbnail(video_data, path);
}
