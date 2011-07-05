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
