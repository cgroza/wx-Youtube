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
