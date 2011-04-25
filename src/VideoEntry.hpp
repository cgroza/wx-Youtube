
#ifndef VIDEOENTRY_H
#define VIDEOENTRY_H

#include <wx/wx.h>
#include "VideoInfo.hpp"

class VideoEntry : public  wxListItem{

public:
    /*Basic constructor.*/
    VideoEntry(VideoInfo* video_data);

    /*Video data getter function. */
    VideoInfo* getVideoData();

    /*Video data setter function.*/
    void setVideoData(VideoInfo* video_data);

private:
    VideoInfo* video;
};


#endif
