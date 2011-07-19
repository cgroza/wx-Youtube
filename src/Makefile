.PHONY: clean all wxyoutube
CFLAGS=-g `wx-config --cxxflags`
LIBS=`wx-config --libs` -lcurl

all: wxyoutube

wxyoutube: Enums.hpp ProgressBar.o Parser.o ImageProc.o ImageBox.o ThumbnailFrame.o VideoInfo.o CommentInfo.o \
CommentsBoard.o VideoDescription.o EventHandler.hpp Events.o EventManager.o DownloadCallback.o SearchURL.o \
XMLFeed.o FeedFetcherThread.o DownloadThread.o VideoEntry.o PrefWindow.o VideoListCtrl.o MainFrame.o MainApp.o


	$(CXX) -o  wx-Youtube Enums.hpp ProgressBar.o Parser.o ImageProc.o ImageBox.o ThumbnailFrame.o VideoInfo.o \
    CommentInfo.o CommentsBoard.o VideoDescription.o EventHandler.hpp Events.o EventManager.o DownloadCallback.o \
    SearchURL.o XMLFeed.o FeedFetcherThread.o DownloadThread.o VideoEntry.o PrefWindow.o VideoListCtrl.o MainFrame.o MainApp.o \
    Extract.hpp Extract.cpp $(CFLAGS) $(LIBS)

clean:
	@$(RM) wx-Youtube *.o

%.o: %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)
