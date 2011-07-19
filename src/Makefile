CC=g++
CFLAGS=-lcurl -g
LIBS=`wx-config --cxxflags --libs`

all: wxyoutube

wxyoutube: Enums.hpp ProgressBar.o Parser.o ImageProc.o ImageBox.o ThumbnailFrame.o VideoInfo.o CommentInfo.o \
CommentsBoard.o VideoDescription.o EventHandler.hpp Events.o EventManager.o DownloadCallback.o SearchURL.o \
XMLFeed.o FeedFetcherThread.o DownloadThread.o VideoEntry.o PrefWindow.o VideoListCtrl.o MainFrame.o MainApp.o


	$(CC) -o  wx-Youtube Enums.hpp ProgressBar.o Parser.o ImageProc.o ImageBox.o ThumbnailFrame.o VideoInfo.o \
    CommentInfo.o CommentsBoard.o VideoDescription.o EventHandler.hpp Events.o EventManager.o DownloadCallback.o \
    SearchURL.o XMLFeed.o FeedFetcherThread.o DownloadThread.o VideoEntry.o PrefWindow.o VideoListCtrl.o MainFrame.o MainApp.o \
    Extract.hpp Extract.cpp $(CFLAGS) $(LIBS)

%.o: %.cpp %.hpp
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)
