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
// Name:        ImageProc.h
// Purpose:     Image processing functions.
// Author:      Alex Thuering
// Created:		18.06.2003
// RCS-ID:      $Id: ImageProc.h,v 1.3 2005/01/07 06:59:18 ntalex Exp $
// Copyright:   (c) Alex Thuering
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef WXVILLALIB_IMAGE_PROC_H
#define IMAGE_PROC_H

#include <wx/wx.h>
#include <wx/image.h>

/** Brightness */
inline int wxGetBrightness(unsigned char r, unsigned char g, unsigned char b)
{ return (wxMax(r, wxMax(g,b))+wxMin(r, wxMin(g,b)))/2; }

inline unsigned char wxAdjustBrightness(unsigned char c, char n)
{ return n<=0 ? c*(n+128)/128 : c + (255-c)*n/128; }

inline void wxAdjustBrightness(
 unsigned char& r, unsigned char& g, unsigned char& b, char n)
{
  r = wxAdjustBrightness(r,n);
  g = wxAdjustBrightness(g,n);
  b = wxAdjustBrightness(b,n);
}

void wxAdjustBrightness(wxImage& img, wxRect rect, char n);
void wxAdjustBrightness(wxImage& img, char n);

/** Adjust to colour */
inline unsigned char wxAdjustToColour(unsigned char src, unsigned char c)
{ return src*c/255; }

inline void wxAdjustToColour(
 unsigned char& r, unsigned char& g, unsigned char& b, const wxColour& c)
{
  r = wxAdjustToColour(r, c.Red());
  g = wxAdjustToColour(g, c.Green());
  b = wxAdjustToColour(b, c.Blue());
}

void wxAdjustToColour(wxImage& img, wxRect rect, wxColour c);
void wxAdjustToColour(wxImage& img, wxColour c);

/** Contrast */
void wxAdjustContrast(wxImage& img, wxRect rect, char n);
void wxAdjustContrast(wxImage& img, char n);

#endif // WXVILLALIB_IMAGE_PROC_H
