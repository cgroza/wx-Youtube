#include "ThumbnailFrame.hpp"
#include <iostream>
BEGIN_EVENT_TABLE(ThumbnailFrame, wxPanel)
// some useful events
/*
 EVT_MOTION(ThumbnailFrame::mouseMoved)
 EVT_LEFT_DOWN(ThumbnailFrame::mouseDown)
 EVT_LEFT_UP(ThumbnailFrame::mouseReleased)
 EVT_RIGHT_DOWN(ThumbnailFrame::rightClick)
 EVT_LEAVE_WINDOW(ThumbnailFrame::mouseLeftWindow)
 EVT_KEY_DOWN(ThumbnailFrame::keyPressed)
 EVT_KEY_UP(ThumbnailFrame::keyReleased)
 EVT_MOUSEWHEEL(ThumbnailFrame::mouseWheelMoved)
 */
 
// catch paint events

EVT_PAINT(ThumbnailFrame::paintEvent)
//Size event
EVT_SIZE(ThumbnailFrame::OnSize)
END_EVENT_TABLE()
 
 
// some useful events
/*
 void ThumbnailFrame::mouseMoved(wxMouseEvent& event) {}
 void ThumbnailFrame::mouseDown(wxMouseEvent& event) {}
 void ThumbnailFrame::mouseWheelMoved(wxMouseEvent& event) {}
 void ThumbnailFrame::mouseReleased(wxMouseEvent& event) {}
 void ThumbnailFrame::rightClick(wxMouseEvent& event) {}
 void ThumbnailFrame::mouseLeftWindow(wxMouseEvent& event) {}
 void ThumbnailFrame::keyPressed(wxKeyEvent& event) {}
 void ThumbnailFrame::keyReleased(wxKeyEvent& event) {}
 */
 
ThumbnailFrame::ThumbnailFrame(wxWindow* parent, const wxPoint& pos, const wxSize& size) :
wxPanel(parent, wxID_ANY, pos, size)
{
    image = new wxImage();
    w = -1;
    h = -1;
}
 
/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
 
void ThumbnailFrame::paintEvent(wxPaintEvent & evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}
 
/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void ThumbnailFrame::paintNow()
{

    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}
 
/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void ThumbnailFrame::render(wxDC&  dc)
{
    int neww, newh;
    dc.GetSize( &neww, &newh );


    if( neww != w || newh != h )
    {
        resized = wxBitmap( image->Scale( neww, newh, wxIMAGE_QUALITY_HIGH ) );
        w = neww;
        h = newh;


        dc.DrawBitmap( resized, 0, 0, false );

    }else{

        dc.DrawBitmap( resized, 0, 0, false );
    }
}
 
/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void ThumbnailFrame::OnSize(wxSizeEvent& event){
     Refresh();
    //skip the event.


    event.Skip();
}
void ThumbnailFrame::ProcessNewThumbnail(VideoInfo* video_data, std::string& path)
{
	// create wxImage and set it to VideoInfo object
	image = new wxImage();
	if(image -> LoadFile( wxString(path.c_str(), wxConvUTF8), wxBITMAP_TYPE_JPEG))
	{
	    video_data -> setImage(image);
	    paintNow();
	}

}


