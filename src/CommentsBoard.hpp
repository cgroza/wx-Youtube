#ifndef COMMENTS_BOARD_H
#define COMMENTS_BOARD_H

#include <wx/wx.h>
#include <vector>
#include <string>
#include "EventManager.hpp"
#include "Events.hpp"
#include "XMLFeed.hpp"
#include "SearchURL.hpp"
#include "Enums.hpp"
#include "Parser.hpp"
#include "VideoInfo.hpp"
#include "CommentInfo.hpp"
#include "FeedFetcherThread.hpp"
#include "DownloadCallback.hpp"
#include <wx/scrolwin.h>


class CommentsPane;
class CommentsBoard : public wxPanel
{
    /*Dispalys and manages video comments.*/
public:
    CommentsBoard(wxWindow* parent, EventManager* evt_man, wxWindowID id = wxID_ANY);

    void DeleteAllComments();	// clears the comment vector

    class CommentsPane : public wxScrolledWindow
    {
    public:
	CommentsPane(CommentsBoard* parent);

	void AddComment(const CommentInfo* comment); // adds a the comment to the text ctrl m_comment_display
	void RefreshCommentList(); // adds every CommentInfo from the m_comments
	void ClearCommentDisplay(); // clears the comment text ctrl
    private:
	wxTextCtrl* m_comment_display; // displays the video comment text
	CommentsBoard* m_parent;
	wxBoxSizer* m_v_sizer;
    };


    friend class FetchCommentsCallback;
    friend class OnVideoSelect;
    friend class OnVideoSearch;
    friend class CommentsPane;

private:

    static const int ON_FEED_FETCHED = 100000; // event ID used to notify this class

    wxBoxSizer* m_v_sizer;
    CommentsPane* m_comments_pane; //comments are displayed in this object instance

//    wxTextCtrl* m_comment_txt;	                  // entry for the user to comment on the video

    static std::vector<CommentInfo*>* m_comments; // holds the video comment objects
    static VideoInfo* m_current_vid;		  // holds the current selected video

    void OnFeedFetched(wxCommandEvent& event); 	// called when the comments feed has been fetched and parsed.
    void FetchCommentsFeed();                   // starts a thread that fetches the comments

    // this callback class is called when the fetcher thread has finished its job.
    class FetchCommentsCallback: public FeedFetcherCallback
    {
    public:
	FetchCommentsCallback(CommentsBoard* parent): m_parent(parent){}
	virtual void operator()(rapidxml::xml_document<>* feed, int exit_code)
	    {
		// create event and post it to parent

		m_parent -> DeleteAllComments(); // clean the old comments, we don't need them anymore

		if(exit_code)
		{ // there was an error when curl fetched the feed.
		    delete feed ; // release the memory and abort the function
		    return;
		}
		// parse and populate received feed

		Parser::parseCommentsFeed(CommentsBoard::m_comments, feed); // parse the xml feed into ComentInfo* objects
		delete feed;		     // free the memorry occupied by the feed, we don't need the feed anymore,
					     // we lready stored the information we need in the m_comments vector

		// Notify the parent that we are done via an event
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, CommentsBoard::ON_FEED_FETCHED);
		event.SetInt(exit_code);
		m_parent -> GetEventHandler() -> AddPendingEvent(event); // add the event to the event queue of m_parent
		return;

	    }
    private:
	CommentsBoard* m_parent;
    };

    // this callback class is called when the user selects a video, it starts the video comment fetching procedure
    class OnVideoSelect: public VideoSelectObjectFunction
    {
    public:
	OnVideoSelect(CommentsBoard* parent) : m_parent(parent) {}
	virtual void operator()(VideoSelectEvent* event)
	    {
		CommentsBoard::m_current_vid = event -> GetVideoInfo(); // get and set the current video
		m_parent -> FetchCommentsFeed(); // start the comment feed fetching procedure

	    }
    private:
	CommentsBoard* m_parent;
    };

    // This callback class  is called when the user gets a new set of vides.
    // Then, we clear the comment display and buffer because they are no longer releveant.
    class OnVideoSearch : public SearchObjectFunction
    {
    public:
	OnVideoSearch(CommentsBoard* parent) : m_parent(parent) {}
	void operator()(VideoSearchEvent*)
	    {
		m_parent -> DeleteAllComments();
		m_parent -> m_comments_pane -> ClearCommentDisplay();

	    }
    private:
	CommentsBoard* m_parent;
    };

    OnVideoSelect* on_select;	// callable class instance
				// it is called when the user selects a video
    OnVideoSearch* on_search;
    DECLARE_EVENT_TABLE()
};


#endif  // COMMENTS_BOARD_H

