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



#include "FeedFetcherThread.hpp"


FeedFetcherThread::FeedFetcherThread(XMLFeed* feed, FeedFetcherCallback* callback)
    : wxThread(), m_callback(callback), m_feed(feed)
{
}

void* FeedFetcherThread::Entry()
{
    if (m_feed -> fetchFeed())
    {
        if(m_callback)
        {
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
