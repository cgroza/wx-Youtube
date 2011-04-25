#include "VideoListCtrl.hpp"


VideoListCtrl::VideoListCtrl(wxWindow* parent) : wxListCtrl(parent){}

void VideoListCtrl::AddVideo(VideoInfo* video_data){
    VideoEntry entry(video_data);
    long item_index = InsertItem(entry);
    SetItem(item_index, 0, wxString(video_data -> getName().c_str(),wxConvUTF8)); //want this for col. 0
    SetItem(item_index, 1, wxString(video_data -> getAuthor().c_str() , wxConvUTF8)); //col. 2

}
