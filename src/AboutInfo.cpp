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



#include "AboutInfo.hpp"
 

AboutInfo::AboutInfo() : wxAboutDialogInfo()
{
    SetVersion(wxT("1.0 Alpha"));
    SetDescription(wxT("Small utility to download youtube videos, based off of youtube-dl."));
    AddDeveloper(wxT("Groza Cristian"));
    AddDeveloper(wxT("N3"));
    SetName(wxT("wx-Youtube")); 
    SetCopyright(wxT("2011 Groza Cristian, N3"));
    SetLicence(wxT(
"   This program is free software: you can redistribute it and/or modify\n"
"   it under the terms of the GNU General Public License as published by\n"
"   the Free Software Foundation, either version 3 of the License, or\n"
"   (at your option) any later version.\n"
"\n"
"   This program is distributed in the hope that it will be useful,\n"
"   but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"   GNU General Public License for more details.\n"
"\n"
"   You should have received a copy of the GNU General Public License\n"
"   along with this program.  If not, see <http://www.gnu.org/licenses/>. \n"
));
}
