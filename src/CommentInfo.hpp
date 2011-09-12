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



#ifndef COMMENT_INFO_H
    #define COMMENT_INFO_H
#include <string>


class CommentInfo
{
public:
    CommentInfo( const std::string& title, const std::string& author, const std::string& content); 		// to be completed
    /*Represent a video comment. Contains the video comment text, and and other information.*/

    virtual std::string getTitle() const;
    virtual std::string getAuthor() const;
    virtual std::string getContent() const;

protected:
    std::string m_title;
    std::string m_author;
    std::string m_content;
};


#endif //COMMENTS_INFO_H
