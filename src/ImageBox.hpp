/////////////////////////////////////////////////////////////////////////////
// Name:        ImageBox.h
// Purpose:     wxImageBox class
// Author:      Alex Thuering
// Created:		8.10.2003
// RCS-ID:      $Id: ImageBox.h,v 1.4 2003/11/06 12:46:59 ntalex Exp $
// Copyright:   (c) Alex Thuering
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef WXVILLALIB_IMAGEBOX_H
#define WXVILLALIB_IMAGEBOX_H

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/filename.h>

/** The widget to display a image buffer. */
class wxPaintBox: public wxScrolledWindow
{
  public:
    wxPaintBox(wxWindow *parent, wxWindowID id = -1);
    ~wxPaintBox() {}
    wxBitmap& GetBuffer() { return *m_buffer; }
    virtual void Update() {}

  protected:
    wxBitmap *m_buffer;
    int m_bufferX, m_bufferY;
    int m_imageWidth, m_imageHeight;
    virtual void OnPaint(wxPaintEvent &event);
    void OnEraseBackground(wxEraseEvent &event);
    DECLARE_EVENT_TABLE()
};

const int scFIT_TO_PAGE = -1;
const int scFIT_TO_WIDTH = -2;
const int scFIT_TO_HEIGHT = -3;

/** The widget to display a image with the zoom function. */
class wxImageBox: public wxPaintBox
{
  public:
	/** Constructs a image box. */
    wxImageBox(wxWindow *parent, wxWindowID id = -1);
	/** Loads an image from a file. */
	bool LoadFile(wxString fname);
	/** Creates a empty image. */
    virtual void Clear();
	/** Returns true if image is not empty. */
    virtual bool IsEmpty();
	
	/** Causes a event to be generated to repaint the image box. */
	virtual void Update();
	/** Repaints the image box.  */
	virtual void UpdatePaintBox();
	
    /** Adjusts a zoom factor/level.
      * Zoom level can be:\n
      *  scFIT_TO_PAGE	 - to fit a image to the image box\n
      *  scFIT_TO_WIDTH  - to fit a image to the width of image box\n
      *  scFIT_TO_HEIGHT - to fit a image to the height of image box\n
     */
    void SetScale(double scale = scFIT_TO_PAGE);
    /** Returns the current zoom factor/level. */
    float GetScale() { return m_scaleV; }
    /** Returns the current zoom factor. */
    float GetScaleValue() { return m_scale; }
    /** Returns the image. */
    wxImage& GetImage() { return m_image; }
	
	/** Sets the pop up menu. */
	void SetPopupMenu(wxMenu* menu) { m_pmenu = menu; }
	/** Returns the pop up menu if it was set, or null otherwise. */
	wxMenu* GetPopupMenu() { return m_pmenu; }

  protected:
    wxImage m_image;
    double m_scale;
    double m_scaleV;
	bool m_repaint;
	wxMenu* m_pmenu;
    bool UpdateScaleValue();
    wxRect getPaintRect();
    virtual void Paint();
	virtual void PaintImg(wxImage& img);
    void OnPaint(wxPaintEvent &event);
    void OnResize(wxSizeEvent &event);
	virtual void OnMouseRightButton(wxMouseEvent &event);
    DECLARE_EVENT_TABLE()
};

wxRect ScaleRect(wxRect rect, double scale);

BEGIN_DECLARE_EVENT_TYPES()
  DECLARE_EVENT_TYPE(EVT_COMMAND_IMAGEBOX_IMAGE_CHANGED, 3300)
END_DECLARE_EVENT_TYPES()

#define EVT_IMAGEBOX_IMAGE_CHANGED(id, fn)\
 DECLARE_EVENT_TABLE_ENTRY(EVT_COMMAND_IMAGEBOX_IMAGE_CHANGED, id,\
 wxID_ANY,\
 (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction)& fn, NULL),

#endif // WXVILLALIB_IMAGEBOX_H
