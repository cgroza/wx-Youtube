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



/////////////////////////////////////////////////////////////////////////////
// Name:        ImageBox.cpp
// Purpose:     wxImageBox class
// Author:      Alex Thuering
// Created:		8.10.2003
// RCS-ID:      $Id: ImageBox.cpp,v 1.4 2005/01/09 15:45:42 ntalex Exp $
// Copyright:   (c) Alex Thuering
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "ImageBox.hpp"
#include "ImageProc.hpp"
#include "math.h"

////////////////////////////////////////////////////////////
////////////////////// wxImageBox //////////////////////////
////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(wxImageBox, wxPaintBox)
  EVT_SIZE(wxImageBox::OnResize)
  EVT_RIGHT_DOWN(wxImageBox::OnMouseRightButton)
  EVT_RIGHT_UP(wxImageBox::OnMouseRightButton)
END_EVENT_TABLE()

DEFINE_EVENT_TYPE(EVT_COMMAND_IMAGEBOX_IMAGE_CHANGED)

wxImageBox::wxImageBox(wxWindow *parent, wxWindowID id) : wxPaintBox(parent, id)
{
  m_scaleV = m_scale = 1;
  m_repaint = false;
  m_pmenu = NULL;
}

void wxImageBox::UpdatePaintBox()
{
  m_repaint = true;
  UpdateScaleValue();
  Refresh();
}

void wxImageBox::Update()
{
  wxCommandEvent evt(EVT_COMMAND_IMAGEBOX_IMAGE_CHANGED, this->GetId());
  GetEventHandler()->ProcessEvent(evt);
  UpdatePaintBox();
}

bool wxImageBox::LoadFile(wxString fname)
{
  if (!GetImage().LoadFile(fname))
    return false;
  Update();
  return true;
}

void wxImageBox::Clear()
{
  GetImage().Create(0,0);
  Update();
}

bool wxImageBox::IsEmpty()
{
  return !GetImage().Ok();
}

void wxImageBox::SetScale(double scale)
{
  m_scaleV = scale;
  UpdatePaintBox();
}

bool wxImageBox::UpdateScaleValue()
{
  if (!GetImage().Ok())
  {
    m_scale = 1;
    return false;
  }
  double old = m_scale;
  m_scale = m_scaleV;
  if (m_scale < 0) // fit to page, width, height
  {
    wxSize page = GetSize();
    wxSize cpage = GetClientSize();
    if ((page.GetWidth() == 0) || (page.GetHeight() == 0))
      return false;
    
    if (m_scale == scFIT_TO_WIDTH)
    {
      m_scale = (double) page.GetWidth()/GetImage().GetWidth();
      if (GetImage().GetHeight()*m_scale > page.GetHeight())
        m_scale = (double) cpage.GetWidth()/GetImage().GetWidth();
    }
    else if (m_scale == scFIT_TO_HEIGHT)
    {
      m_scale = (double) page.GetHeight()/GetImage().GetHeight();
      if (GetImage().GetWidth()*m_scale > page.GetWidth())
        m_scale = (double) cpage.GetHeight()/GetImage().GetHeight();
    }
    else //if (m_scale == scFIT_TO_PAGE)
    {
      m_scale = (double) page.GetWidth()/GetImage().GetWidth();
      if (m_scale > (double) page.GetHeight()/GetImage().GetHeight())
      m_scale = (double) page.GetHeight()/GetImage().GetHeight();
    }
  }
  //wxMessageBox(wxString::Format("%f", m_scale));
  return old != m_scale;
}

wxRect wxImageBox::getPaintRect()
{
  wxSize size = GetClientSize();
  wxRect paintRect(0, 0, size.GetWidth(), size.GetHeight());
  GetViewStart(&paintRect.x, &paintRect.y);
  int xu,yu;
  GetScrollPixelsPerUnit(&xu, &yu);
  paintRect.x *= xu; paintRect.y *= yu;
  return paintRect;
}

void wxImageBox::Paint()
{
  // image width & height
  m_imageWidth = (int) (GetImage().GetWidth()*m_scale);
  m_imageHeight = (int) (GetImage().GetHeight()*m_scale);
  if (m_imageWidth == 0 || m_imageHeight == 0)
  {
	delete m_buffer;
	m_buffer = new wxBitmap(0,0);
    return;
  }
  
  // get paintRect
  wxRect paintRect = getPaintRect();
  // make buffer 2 times as big as visible area (paintRect)
  paintRect.x -= paintRect.width/2; if (paintRect.x < 0) paintRect.x = 0;
  paintRect.y -= paintRect.height/2; if (paintRect.y < 0) paintRect.y = 0;
  paintRect.width *= 2;
  paintRect.height *= 2;
  
  if (paintRect.GetRight() > m_imageWidth)
    paintRect.width = m_imageWidth - paintRect.x;
  if (paintRect.GetBottom() > m_imageHeight)
    paintRect.height = m_imageHeight - paintRect.y;
  
  m_bufferX = paintRect.x;
  m_bufferY = paintRect.y;
  
  // scale
  //wxImage img = GetImage().Scale(m_imageWidth, m_imageHeight);
  wxRect subRect = ScaleRect(paintRect, 1/m_scale);
  wxImage img;
  int imgw = GetImage().GetWidth();
  int imgh = GetImage().GetHeight();
  // if subRect equal image (+-1%)
  if (subRect.x*100/imgw!=0 || subRect.y*100/imgh!=0 ||
     (subRect.width-imgw)*100/imgw!=0 || (subRect.height-imgh)*100/imgh!=0)
    img = GetImage().GetSubImage(subRect);
  else
    img = GetImage();
  img = img.Scale(paintRect.width, paintRect.height);
  
  PaintImg(img);
  delete m_buffer;
  m_buffer = new wxBitmap(img);
}

void wxImageBox::PaintImg(wxImage& img)
{
}

void wxImageBox::OnPaint(wxPaintEvent &event)
{
  wxRect paintRect = getPaintRect();
  if (paintRect.GetRight() >= m_imageWidth)
    paintRect.width = m_imageWidth - paintRect.x;
  if (paintRect.GetBottom() >= m_imageHeight)
    paintRect.height = m_imageHeight - paintRect.y;
  wxRect bufferRect(m_bufferX, m_bufferY,
	m_buffer->GetWidth(), m_buffer->GetHeight());
  if (m_repaint ||
      paintRect.x < bufferRect.x ||
      paintRect.y < bufferRect.y ||
      paintRect.GetRight() > bufferRect.GetRight() ||
      paintRect.GetBottom() > bufferRect.GetBottom())
  {
    Paint(); // update buffer
    m_repaint = false;
    //wxLogMessage("Repaint: %d,%d - %d,%d -> %d,%d - %d,%d",
    // paintRect.x, paintRect.y, paintRect.width, paintRect.height,
    // bufferRect.x, bufferRect.y, bufferRect.width, bufferRect.height);
  }
  wxPaintBox::OnPaint(event);
}

void wxImageBox::OnResize(wxSizeEvent &event)
{
  UpdatePaintBox();
}

void wxImageBox::OnMouseRightButton(wxMouseEvent &event)
{
  if (event.RightUp() && m_pmenu)
	PopupMenu(m_pmenu, event.GetPosition());
}

////////////////////////////////////////////////////////////
///////////////////// wxPaintBox ///////////////////////////
////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(wxPaintBox, wxScrolledWindow)
  EVT_PAINT(wxPaintBox::OnPaint)
  EVT_ERASE_BACKGROUND(wxPaintBox::OnEraseBackground)
END_EVENT_TABLE()

wxPaintBox::wxPaintBox(wxWindow *parent, wxWindowID id):
    wxScrolledWindow(parent, id)
{
  SetScrollRate(1,1);
  m_buffer = new wxBitmap;
  m_bufferX = m_bufferY = 0;
  m_imageWidth = m_imageHeight = 0;
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_LISTBOX));
}

void wxPaintBox::OnPaint(wxPaintEvent& WXUNUSED(event))
{
  SetVirtualSize(m_imageWidth, m_imageHeight);
  
  wxPaintDC dc(this);  
  PrepareDC(dc);
  dc.BeginDrawing();
  dc.DrawBitmap(*m_buffer, m_bufferX, m_bufferY);
  //background
  dc.SetPen(wxPen(*wxBLACK,0,wxTRANSPARENT));
  dc.SetBrush(wxBrush(GetBackgroundColour(), wxSOLID));
  int w = wxMax(GetClientSize().GetWidth(), m_imageWidth);
  int h = wxMax(GetClientSize().GetHeight(), m_imageHeight);
  dc.DrawRectangle(m_imageWidth, 0, w-m_imageWidth, h+50);
  dc.DrawRectangle(0, m_imageHeight, w, h-m_imageHeight+50);
  dc.EndDrawing();
}

void wxPaintBox::OnEraseBackground(wxEraseEvent &event)
{
}

////////////////////////////////////////////////////////////
////////////////// Help functions //////////////////////////
////////////////////////////////////////////////////////////

wxRect ScaleRect(wxRect rect, double scale)
{
  wxRect res;
  res.x = (int) (rect.x*scale);  
  res.y = (int) (rect.y*scale);
  res.width = (int) (rect.width*scale);
  res.height = (int) (rect.height*scale);
  return res;
}

