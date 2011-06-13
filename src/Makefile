CC=g++
CFLAGS=-lcurl
LIBS=`wx-config --cxxflags --libs`

all: wxyoutube

wxyoutube: Enums.hpp Parser.o ImageProc.o ImageBox.o ThumbnailFrame.o VideoInfo.o DownloadCallback.o SearchURL.o XMLFeed.o DownloadThread.o VideoEntry.o PrefWindow.o VideoListCtrl.o MainFrame.o MainApp.o
	$(CC) -o  Youtube-wx Enums.hpp Parser.o ImageProc.o ImageBox.o ThumbnailFrame.o VideoInfo.o DownloadCallback.o SearchURL.o XMLFeed.o DownloadThread.o VideoEntry.o PrefWindow.o VideoListCtrl.o MainFrame.o MainApp.o $(CFLAGS) $(LIBS)

XMLFeed.o: XMLFeed.hpp XMLFeed.cpp
	$(CC) -c -o XMLFeed.o  XMLFeed.cpp  $(CFLAGS) $(LIBS)

VideoInfo.o:  VideoInfo.hpp VideoInfo.cpp
	$(CC) -c -o VideoInfo.o  VideoInfo.cpp $(CFLAGS) $(LIBS)

SearchURL.o:  SearchURL.hpp SearchURL.cpp
	$(CC) -c -o SearchURL.o  SearchURL.cpp $(CFLAGS) $(LIBS)

DownloadThread.o:  DownloadThread.hpp DownloadThread.cpp
	$(CC) -c -o DownloadThread.o  DownloadThread.cpp $(CFLAGS) $(LIBS)

VideoEntry.o:  VideoEntry.hpp VideoEntry.cpp
	$(CC) -c -o VideoEntry.o  VideoEntry.cpp $(CFLAGS) $(LIBS)

VideoListCtrl.o:   VideoListCtrl.hpp VideoListCtrl.cpp
	$(CC) -c -o VideoListCtrl.o  VideoListCtrl.cpp $(CFLAGS) $(LIBS)

PrefWindow.o:    PrefWindow.hpp PrefWindow.cpp
	$(CC) -c -o PrefWindow.o  PrefWindow.cpp $(CFLAGS) $(LIBS)

MainFrame.o:  MainFrame.hpp MainFrame.cpp
	$(CC) -c -o MainFrame.o  MainFrame.cpp $(CFLAGS) $(LIBS)

MainApp.o:  MainApp.hpp MainApp.cpp
	$(CC) -c -o MainApp.o  MainApp.cpp $(CFLAGS) $(LIBS)

ThumbnailFrame.o: ThumbnailFrame.hpp ThumbnailFrame.cpp
	$(CC) -c -o ThumbnailFrame.o ThumbnailFrame.cpp $(CFLAGS) $(LIBS)

Parser.o: Parser.hpp Parser.cpp
	$(CC) -c -o Parser.o Parser.cpp $(CFLAGS) $(LIBS)

DownloadCallback.o: DownloadCallback.hpp DownloadCallback.cpp
	$(CC) -c -o DownloadCallback.o DownloadCallback.cpp $(CFLAGS) $(LIBS)

ImageProc.o: ImageProc.hpp ImageProc.cpp
	$(CC) -c -o ImageProc.o ImageProc.cpp $(CFLAGS) $(LIBS)

ImageBox.o: ImageBox.hpp ImageBox.cpp
	$(CC) -c -o ImageBox.o ImageBox.cpp $(CFLAGS) $(LIBS)



#Enums.o: Enums.hpp 
#	$(CC) -c -o Enums.o Enums.hpp $(CFLAGS) $(LIBS)

