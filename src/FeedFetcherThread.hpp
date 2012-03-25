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



#ifndef FEED_FETCHER_THREAD_H
#define FEED_FETCHER_THREAD_H
#include "DownloadCallback.hpp"
#include "XMLFeed.hpp"
#include <wx/thread.h>

class FeedFetcherThread : public wxThread
{
private:
    FeedFetcherCallback* m_callback;
    XMLFeed* m_feed;
/* Takes a XMLFeed as an argument, runs it and calls the provided callback with a rapidxml::xml_document as an argument and the curl exit code.   */
public:
    FeedFetcherThread(XMLFeed* feed, FeedFetcherCallback* callback = 0);
    ~FeedFetcherThread();
    virtual void* Entry();
};
#endif //FEED_FETCHER_THREAD_H
