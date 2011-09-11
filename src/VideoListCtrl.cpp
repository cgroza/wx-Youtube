#include "VideoListCtrl.hpp"

VideoListCtrl::VideoListCtrl(wxWindow* parent) : wxListView(parent, LIST_Video_list, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL){

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
    
    
    
    long item_index = InsertItem(*entry);
    SetItem(item_index, 0, wxString(video_data -> getName().c_str(),wxConvUTF8)); //want this for col. 0
    SetItem(item_index, 1, wxString(video_data -> getAuthor().c_str() , wxConvUTF8)); //col. 1
    SetItem(item_index, 2, wxString(video_data -> getRating().substr(0, 3).c_str(), wxConvUTF8)); //col 2
    SetItem(item_index, 3, wxString(video_data -> getViews().c_str(),wxConvUTF8)); //col 3
    entries.push_back(entry);
}

VideoEntry* VideoListCtrl::GetVideoEntry(long index)
{
    // we are deducing the real position of the required entry.
    // the order of the entries vector elements is renversed relatively to the
    // video list order, so we must do some math to get the right position
    return entries[entries.size() - index - 1]; // we must substract 1 because size() is 1 based

    // an alternative approach is to reverse the entries vector each time we are done populating it.
}

bool VideoListCtrl::DeleteAllItems()
{
    entries.clear();
    wxListView::DeleteAllItems();

}
