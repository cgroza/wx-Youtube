#ifndef FEED_FETCHER_THREAD_H
#define FEED_FETCHER_THREAD_H
#include "DownloadCallback.hpp"
#include "XMLFeed.hpp"


class FeedFetcherThread : public wxThread
{
/* Takes a XMLFeed as an argument, runs it and calls the provided callback with a rapidxml::xml_document as an argument and the curl exit code.   */
public:
    FeedFetcherThread(FeedFetcherCallback* callback, XMLFeed* feed);
    ~FeedFetcherThread();
    virtual void* Entry();

private:
    FeedFetcherCallback* m_callback;
    XMLFeed* m_feed;
};


#endif //FEED_FETCHER_THREAD_H
