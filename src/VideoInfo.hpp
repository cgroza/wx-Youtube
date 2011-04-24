#ifndef VIDEOINFO_H
#define VIDEOINFO_H
#include <string>

class VideoInfo
{
    public:
        VideoInfo(const std::string& name = "None", const std::string& link = "None", const std::string& descr = "None", const std::string& author = "None");

        virtual std::string getName() const;
        virtual std::string getLink() const;
        virtual std::string getDescription() const;
        virtual std::string getAuthor() const;

    protected:
        std::string m_name;
        std::string m_link;
        std::string m_description;
        std::string m_author;

    private:
};

#endif // VIDEOINFO_H
