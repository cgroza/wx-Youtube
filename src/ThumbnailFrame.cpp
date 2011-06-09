#include "ThumbnailFrame.hpp"

ThumbnailFrame::ThumbnailFrame(): wxScrolledWindow(), bitmap(0,0)
{


}

void ThumbnailFrame::Create(wxWindow *parent, wxWindowID id)
{
        wxScrolledWindow::Create(parent, id);
}

void ThumbnailFrame::LoadImage(wxImage &image)
{
        bitmap = wxBitmap(image);
        SetVirtualSize(bitmap.GetWidth(), bitmap.GetHeight());
        wxClientDC dc(this);
        PrepareDC(dc);
        dc.DrawBitmap(bitmap, 0, 0);

}

void ThumbnailFrame::OnMouse(wxMouseEvent &event)
{
        int xx,yy;
        CalcUnscrolledPosition(event.GetX(), event.GetY(), &xx, &yy);
        event.m_x = xx; event.m_y = yy;
        event.ResumePropagation(1); // Pass along mouse events (e.g. to parent)
        event.Skip();

}

void ThumbnailFrame::OnPaint(wxPaintEvent &event)
{
        wxPaintDC dc(this);
        PrepareDC(dc);
        dc.DrawBitmap(bitmap, 0,0, true);

}


BEGIN_EVENT_TABLE(ThumbnailFrame,wxScrolledWindow)
    EVT_PAINT(ThumbnailFrame::OnPaint)
    EVT_MOUSE_EVENTS(ThumbnailFrame::OnMouse)
END_EVENT_TABLE()
