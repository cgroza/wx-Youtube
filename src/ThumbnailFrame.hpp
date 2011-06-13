#ifndef THUMB_NAIL_FRAME_H
    #define THUMB_NAIL_FRAME_H

#include "VideoInfo.hpp"
#include <string>
#include "ImageBox.hpp"


class ThumbnailFrame : public wxImageBox
{
public:
    ThumbnailFrame(wxWindow* parent, wxWindowID id = -1);
    void SetThumbnail(wxImage& image);
    void ProcessNewThumbnail(VideoInfo* video_data, std::string& path );
};

#endif // THUMBNAIL_FRAME_H
