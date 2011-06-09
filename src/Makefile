CC=g++
CFLAGS=-lcurl
LIBS=`wx-config --cxxflags --libs`

all: wxyoutube

wxyoutube: Enums.hpp ThumbnailFrame.o VideoInfo.o SearchURL.o VideoSearch.o DownloadThread.o VideoEntry.o PrefWindow.o VideoListCtrl.o MainFrame.o MainApp.o
	$(CC) -o  Youtube-wx Enums.hpp ThumbnailFrame.o VideoInfo.o SearchURL.o VideoSearch.o DownloadThread.o VideoEntry.o PrefWindow.o VideoListCtrl.o MainFrame.o MainApp.o $(CFLAGS) $(LIBS)

VideoSearch.o: VideoSearch.hpp VideoSearch.cpp
	$(CC) -c -o VideoSearch.o  VideoSearch.cpp  $(CFLAGS) $(LIBS)

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

#Enums.o: Enums.hpp 
#	$(CC) -c -o Enums.o Enums.hpp $(CFLAGS) $(LIBS)

