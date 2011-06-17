#include "Events.hpp"

VideoSearchEvent::VideoSearchEvent(std::vector<VideoInfo*>* search_results) : m_results(search_results)
{

}

std::vector<VideoInfo*>* VideoSearchEvent::GetResults() const
{
    return m_results;
}


VideoSelectEvent::VideoSelectEvent(VideoInfo* video_info) : m_video_info(video_info)
{
}


VideoInfo* VideoSelectEvent::GetVideoInfo() const
{
    return m_video_info;
}

