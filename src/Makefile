.PHONY: clean all wxyoutube
CFLAGS=-g `wx-config --cxxflags`
LIBS=`wx-config --libs` -lcurl
RM=rm

GLOBAL_HEADERS = Enums.hpp
CPPFILES = $(wildcard *.cpp)
# CPPFILES = ProgressBar.cpp Parser.cpp ImageProc.cpp ImageBox.cpp \
# 	   ThumbnailFrame.cpp VideoInfo.cpp CommentInfo.cpp CommentsBoard.cpp \
# 	   VideoDescription.cpp EventHandler.hpp Events.cpp EventManager.cpp \
# 	   DownloadCallback.cpp SearchURL.cpp XMLFeed.cpp FeedFetcherThread.cpp \
# 	   DownloadThread.cpp VideoEntry.cpp PrefWindow.cpp VideoListCtrl.cpp \
# 	   MainFrame.cpp MainApp.cpp Extract.cpp

all: wxyoutube desktop_file

wxyoutube: $(GLOBAL_HEADERS) $(CPPFILES:.cpp=.o)
	$(CXX) -o wx-Youtube $^ $(CFLAGS) $(LIBS)

desktop_file:
	cp ../wx-youtube.desktop ${HOME}/.local/share/applications
	
clean:
	@$(RM) wx-Youtube *.o

%.o: %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CFLAGS)

