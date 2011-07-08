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


class CommentsBoard : public wxPanel
{
    /*Dispalys and manages video comments.*/
public:
    CommentsBoard(wxWindow* parent, EventManager* evt_man, wxWindowID id = wxID_ANY);

    void OnFeedFetched();
    void FetchCommentsFeed();//populates the m_comments


    friend class FetchCommentsCallback;
    friend class OnVideoSelect;

    class CommentRect : public wxPanel
    {
    public:
	/*Displays and manages controls for a single video comment.*/
	CommentRect(wxWindow* parent, CommentInfo* comment, wxWindowID id = wxID_ANY);
	~CommentRect();
    protected:
	wxBoxSizer* m_v_sizer;
	wxStaticText* m_comment_txt;
	CommentInfo* m_comment_info;
    };

protected:
    wxBoxSizer* m_v_sizer;
    wxPanel* m_comments_pane;
    wxTextCtrl* m_comment_txt;
    static std::vector<CommentInfo*>* m_comments;
    static VideoInfo* m_current_vid;

    class FetchCommentsCallback: public FeedFetcherCallback
    {
    public:
	FetchCommentsCallback(CommentsBoard* parent): m_parent(parent){}
	virtual void operator()(rapidxml::xml_document<>* feed, int exit_code)
	    {
		// delete the old comments
		// create iterator
		std::vector<CommentInfo*>::iterator del = m_comments -> begin();
		for(del; del < m_comments -> end(); ++del) 
		{
		    delete *del;
		    *del = 0;	// delete comment and set pointer to NULL
		}

		if(exit_code) delete feed ;return; // there was an error when curl fetched the feed.
		// parse and populate received feed
		Parser::parseCommentsFeed(CommentsBoard::m_comments, feed);
		m_parent -> OnFeedFetched(); // notify the comments board that the comments vector has been populated
		delete feed;		     // free the memorry occupied by the feed
	    }
    private:
	CommentsBoard* m_parent;
    };


    class OnVideoSelect: public VideoSelectObjectFunction
    {
    public:
	OnVideoSelect(CommentsBoard* parent) : m_parent(parent) {}
	virtual void operator()(VideoSelectEvent* event)
	    {
		CommentsBoard::m_current_vid = event -> GetVideoInfo();
		m_parent -> FetchCommentsFeed();

	    }
    private:
	CommentsBoard* m_parent;
    };

private:
    OnVideoSelect* on_select;
};
#endif  // COMMENTS_BOARD_H
