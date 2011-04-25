#include "VideoEntry.hpp"

VideoEntry::VideoEntry(VideoInfo* video_data): wxListItem(), video(video_data){}

VideoInfo* VideoEntry::getVideoData()  {   return video;}

void VideoEntry::setVideoData(VideoInfo* video_data){
        video = video_data;
}
