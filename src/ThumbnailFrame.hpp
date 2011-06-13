#ifndef THUMB_NAIL_FRAME_H
    #define THUMB_NAIL_FRAME_H

#include "VideoInfo.hpp"
#include <string>
#include <wx/wx.h>
#include <wx/sizer.h>
 
class ThumbnailFrame : public wxPanel
{
    wxImage* image;
    wxBitmap resized;
    int w, h;
    
public:
    ThumbnailFrame(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& = wxDefaultSize);
    
    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);
    void ProcessNewThumbnail(VideoInfo* video_data, std::string& path);
    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */
    
    DECLARE_EVENT_TABLE()

};




#endif // THUMBNAIL_FRAME_H
