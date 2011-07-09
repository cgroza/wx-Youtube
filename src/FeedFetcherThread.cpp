#include "FeedFetcherThread.hpp"


FeedFetcherThread::FeedFetcherThread(XMLFeed* feed, FeedFetcherCallback* callback)
    : wxThread(), m_callback(callback), m_feed(feed)
{
}

void* FeedFetcherThread::Entry()
{
    if (m_feed -> fetchFeed())
    {
	if(m_callback){

	    m_callback -> operator()(m_feed ->getXMLFeed(), m_feed -> getErrorCode());

	}
    }

}

FeedFetcherThread::~FeedFetcherThread()
{
    if(m_callback)
    {
	delete m_callback;
	m_callback = 0;
    }
}
