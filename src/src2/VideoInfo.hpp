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



#ifndef VIDEOINFO_H
#define VIDEOINFO_H
#include <string>
#include <wx/wx.h>




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
	virtual ~VideoInfo();

        virtual std::string getName() const;
        virtual std::string getLink() const;
        virtual std::string getDescription() const;
        virtual std::string getAuthor() const;
        virtual std::string getRating() const;
        virtual std::string getViews() const;
        virtual std::string getId() const;
        virtual std::string getThumbnail() const;
	virtual wxImage* getImage() const;
        virtual void setImage( wxImage* img );

    protected:
        std::string m_name;
        std::string m_rating;
        std::string m_views;
        std::string m_link;
        std::string m_description;
        std::string m_author;
        std::string m_id;
        std::string m_thumbnail;
        wxImage* m_image;

    private:
};

#endif // VIDEOINFO_H
