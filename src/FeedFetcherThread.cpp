#include "FeedFetcherThread.hpp"


FeedFetcherThread::FeedFetcherThread(FeedFetcherCallback* callback, XMLFeed* feed)
    :m_callback(callback), m_feed(feed)
{
}

void* FeedFetcherThread::Entry()
{
    if (m_feed -> fetchFeed()) m_callback -> operator()(m_feed ->getXMLFeed(), m_feed -> getErrorCode());
    
}

FeedFetcherThread::~FeedFetcherThread()
{
    delete m_callback;
}
