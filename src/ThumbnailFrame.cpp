//Copyright (C) 2011  Groza Cristian, N3
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



#include "ThumbnailFrame.hpp"

ThumbnailFrame::ThumbnailFrame(wxWindow* parent, wxWindowID id) : wxImageBox(parent, id)
{

}

void ThumbnailFrame::SetThumbnail(wxImage& image)
{
    m_image = image;
    SetScale(scFIT_TO_PAGE);
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


