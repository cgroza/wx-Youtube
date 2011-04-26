#include "VideoListCtrl.hpp"
#include "Enums.hpp"
#include "VideoInfo.hpp"

VideoListCtrl::VideoListCtrl(wxWindow* parent) : wxListCtrl(parent, LIST_Video_list, wxDefaultPosition, wxSize(600,400), wxLC_REPORT | wxLC_SINGLE_SEL){

    //setting up the columns.

    //Title
    itemTitle.SetText(wxT("Title"));
    InsertColumn(0, itemTitle);
    SetColumnWidth(0, 200);

    //Rating

    itemRating.SetText(wxT("Rating"));
    InsertColumn(1, itemRating);
    SetColumnWidth(1, 100);

    //Description

    itemDescription.SetText(wxT("Description"));
    InsertColumn(2, itemDescription);
    SetColumnWidth(2, 300);

}

void VideoListCtrl::AddVideo(VideoInfo* video_data){
    VideoEntry entry(video_data);

    long int item_index = InsertItem(entry);
    SetItem(item_index, 0, wxString(video_data -> getName().c_str(),wxConvUTF8)); //want this for col. 0
    SetItem(item_index, 2, wxString(video_data -> getAuthor().c_str() , wxConvUTF8)); //col. 2

}
