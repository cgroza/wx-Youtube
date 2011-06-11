#include "VideoInfo.hpp"

VideoInfo::VideoInfo(const std::string& name,
                      const std::string& rating,
                       const std::string& views ,
                        const std::string& link,
                         const std::string& descr,
                          const std::string& author,
                           const std::string& id,
                            const std::string& thumbnail):
    m_name(name), m_rating(rating), m_views(views) ,m_link(link),
    m_description(descr), m_author(author), m_id(id), m_thumbnail(thumbnail)
{

}

std::string VideoInfo::getName() const{
    return m_name;
}

std::string VideoInfo::getLink() const{
    return m_link;
}

std::string VideoInfo::getDescription() const{
    return m_description;
}

std::string VideoInfo::getAuthor() const{
    return m_author;
}

std::string VideoInfo::getRating() const{
    return m_rating;
}

std::string VideoInfo::getViews() const{
    return m_views;
}

std::string VideoInfo::getId() const{
    return m_id;
}

std::string VideoInfo::getThumbnail() const{
    return m_thumbnail;
}

wxImage* VideoInfo::getImage() const
{
    return m_image;
}

void VideoInfo::setImage(wxImage* img)
{
    m_image = img;
}
