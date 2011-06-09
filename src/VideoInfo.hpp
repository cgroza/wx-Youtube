#ifndef VIDEOINFO_H
#define VIDEOINFO_H
#include <string>

class VideoInfo
{
    public:
        VideoInfo(const std::string& name = "N/A",
                   const std::string& rating = "N/A",
                    const std::string& views = "N/A",
                     const std::string& link = "N/A",
                      const std::string& descr = "N/A",
                       const std::string& author = "N/A",
                        const std::string& id = "N/A",
                         const std::string& thumbnail = "N/A");

        virtual std::string getName() const;
        virtual std::string getLink() const;
        virtual std::string getDescription() const;
        virtual std::string getAuthor() const;
        virtual std::string getRating() const;
        virtual std::string getViews() const;
        virtual std::string getId() const;
        virtual std::string getThumbnail() const;
    protected:
        std::string m_name;
        std::string m_rating;
        std::string m_views;
        std::string m_link;
        std::string m_description;
        std::string m_author;
        std::string m_id;
        std::string m_thumbnail;

    private:
};

#endif // VIDEOINFO_H
