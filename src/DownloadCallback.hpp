#ifndef DOWNLOAD_CALLBACK_H
    #define DOWNLOAD_CALLBACK_H
#include "VideoInfo.hpp"
#include "ThumbnailFrame.hpp"
#include <string>
#include "XMLFeed.hpp"

class DownloadCallback
{
public:

    virtual void operator()(VideoInfo* video_data, std::string& path) = 0;

};



class ThumbnailDownloadCallback: public DownloadCallback
{
public:
    ThumbnailDownloadCallback(ThumbnailFrame* thumb_obj);
    virtual void operator()(VideoInfo* video_data, std::string& path);
private:
    ThumbnailFrame* m_thumb_obj;
};

class EnableWidgetCallback: public DownloadCallback
{
public:
  EnableWidgetCallback(wxWindow* widget);
  virtual void operator()(VideoInfo* , std::string& ); // dummy prototype
protected:
  wxWindow* m_widget;
};


class FeedFetcherCallback
{
public:
    virtual void operator()(rapidxml::xml_document<>*, int) = 0;
};

#endif	// DOWNLOAD_CALLBACK_H
