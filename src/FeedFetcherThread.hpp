#ifndef FEED_FETCHER_THREAD_H
#define FEED_FETCHER_THREAD_H
#include "DownloadCallback.hpp"
#include "XMLFeed.hpp"
#include <wx/thread.h>

class FeedFetcherThread : public wxThread
{
/* Takes a XMLFeed as an argument, runs it and calls the provided callback with a rapidxml::xml_document as an argument and the curl exit code.   */
public:
    FeedFetcherThread(XMLFeed* feed, FeedFetcherCallback* callback = 0);
    ~FeedFetcherThread();
    virtual void* Entry();

private:
    FeedFetcherCallback* m_callback;
    XMLFeed* m_feed;
};


#endif //FEED_FETCHER_THREAD_H
