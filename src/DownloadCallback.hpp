#ifndef DOWNLOAD_CALLBACK_H
    #define DOWNLOAD_CALLBACK_H
#include "VideoInfo.hpp"
#include "ThumbnailFrame.hpp"
#include <string>


class DownloadCallback
{
public:

    virtual void operator()(VideoInfo* video_data, std::string& path);

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

#endif	// DOWNLOAD_CALLBACK_H
