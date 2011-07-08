#ifndef COMMENTS_BOARD_H
#define COMMENTS_BOARD_H

#include <wx/wx.h>
#include <vector>
#include <string>
#include "EventManager.hpp"
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

    friend class FetchCommentsCallback;

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
    std::vector<CommentInfo*>* m_comments;
    VideoInfo* m_current_vid;

    class FetchCommentsCallback: public FeedFetcherCallback
    {
    public:
	FetchCommentsCallback(CommentsBoard* parent): m_parent(parent){}
	virtual void operator()(rapidxml::xml_document<>* feed, int exit_code)
	    {
		if(exit_code) return; // there was an error when curl fetched the feed.
		// parse and populate received feed
		Parser::parseCommentsFeed(m_parent -> m_comments, feed);
		m_parent -> OnFeedFetched(); // notify the comments board that the comments vector has been populated
	    }
    private:
	CommentsBoard* m_parent;
    };

private:
    void FetchCommentsFeed();//populates the m_comments
};
#endif  // COMMENTS_BOARD_H
