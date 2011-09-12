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



#include "CommentInfo.hpp"

CommentInfo::CommentInfo( const std::string& title, const std::string& author, const std::string& content)
    : m_title(title), m_author(author), m_content(content)
{

}

std::string CommentInfo::getTitle() const
{
    return m_title;
}

std::string CommentInfo::getAuthor() const
{
    return m_author;
}

std::string CommentInfo::getContent() const
{
    return m_content;
}
