#include "ThumbnailFrame.hpp"

ThumbnailFrame::ThumbnailFrame(wxWindow* parent, wxWindowID id) : wxImageBox(parent, id)
{

}

void ThumbnailFrame::SetThumbnail(wxImage& image)
{
    m_image = image;
    Update();
}

void ThumbnailFrame::ProcessNewThumbnail(VideoInfo* video_data, std::string& path)
{
	// create wxImage and set it to VideoInfo object
	wxImage* image = new wxImage();

	if(image -> LoadFile( wxString(path.c_str(), wxConvUTF8), wxBITMAP_TYPE_JPEG))
	{
	    video_data -> setImage(image);
	    SetThumbnail(*image);
	}

}


