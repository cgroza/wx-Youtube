#include "VideoEntry.hpp"

VideoEntry::VideoEntry(VideoInfo* video_data): wxListItem(), video(video_data){}

VideoInfo* VideoEntry::getVideoData()
{
if (video != 0) return video;
else return 0;
}

void VideoEntry::setVideoData(VideoInfo* video_data){
        video = video_data;
}
