#include "VideoListCtrl.hpp"
#include "Enums.hpp"
#include "VideoInfo.hpp"

VideoListCtrl::VideoListCtrl(wxWindow* parent) : wxListView(parent, LIST_Video_list, wxDefaultPosition, wxSize(600,400), wxLC_REPORT | wxLC_SINGLE_SEL){

    //setting up the columns.

    //Title
    itemTitle.SetText(wxT("Title"));
    InsertColumn(0, itemTitle);
    SetColumnWidth(0, 200);

    //Author

    itemAuthor.SetText(wxT("Author"));
    InsertColumn(1, itemAuthor);
    SetColumnWidth(1, 100);

    //Rating
    itemRating.SetText(wxT("Rating"));
    InsertColumn(2, itemRating);
    SetColumnWidth(2, 100);

    //Views

    itemViews.SetText(wxT("Views"));
    InsertColumn(3, itemViews);
    SetColumnWidth(3, 100);

}

void VideoListCtrl::AddVideo(VideoInfo* video_data){
    VideoEntry* entry = new VideoEntry(video_data);

    long int item_index = InsertItem(*entry);
    SetItem(item_index, 0, wxString(video_data -> getName().c_str(),wxConvUTF8)); //want this for col. 0
    SetItem(item_index, 1, wxString(video_data -> getAuthor().c_str() , wxConvUTF8)); //col. 1
    SetItem(item_index, 2, wxString(video_data -> getRating().c_str(),wxConvUTF8)); //col 2
    SetItem(item_index, 3, wxString(video_data -> getViews().c_str(),wxConvUTF8)); //col 3
    entries.push_back(entry);
}

VideoEntry* VideoListCtrl::GetVideoEntry(long index)
{
    return entries[index];
}

bool VideoListCtrl::DeleteAllItems()
{
    entries.clear();
    wxListView::DeleteAllItems();

}
