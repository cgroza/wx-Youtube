#ifndef THUMB_NAIL_FRAME_H
    #define THUMB_NAIL_H
#include <wx/wx.h>


// A scrolled window for showing an image.
class ThumbnailFrame: public wxScrolledWindow
{   
public:
    ThumbnailFrame();

    void Create(wxWindow *parent, wxWindowID id = -1);


    void LoadImage(wxImage &image);

protected:
    wxBitmap bitmap;

    void OnMouse(wxMouseEvent &event);

    void OnPaint(wxPaintEvent &event);

private:
    DECLARE_EVENT_TABLE()
};

#endif // THUMBNAIL_FRAME_H
