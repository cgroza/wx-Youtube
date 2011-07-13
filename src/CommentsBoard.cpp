#include "CommentsBoard.hpp"

CommentsBoard::CommentsBoard(wxWindow* parent, EventManager* evt_man, wxWindowID id): wxPanel(parent), m_v_sizer(0),
							      m_comments_pane(0), m_comments_v_sizer(0)
{
    // create the event handler an bind it
    on_select = new OnVideoSelect(this);
    evt_man -> BindSelectVideoEvent(on_select);

    m_v_sizer = new wxBoxSizer(wxVERTICAL);

    m_comments_pane = new wxPanel(this);
    m_comments_v_sizer = new wxBoxSizer(wxVERTICAL);
    m_comments_pane -> SetSizerAndFit(m_comments_v_sizer);

    m_comment_txt = new wxTextCtrl(this, wxID_ANY);
    m_v_sizer -> Add(m_comments_pane, 3, wxEXPAND | wxALL, 0);
    m_v_sizer -> Add(m_comment_txt, 1, wxEXPAND | wxALL, 0);

}

void CommentsBoard::AddComment(CommentInfo* comment)
{
    CommentRect* comment_rect = new CommentRect(m_comments_pane, comment);
    m_comments_v_sizer -> Add(comment_rect, 0, wxEXPAND|wxALL, 0);
    m_comments_pane -> Layout();
}

void CommentsBoard::DeleteAllComments()
{
    // delete the old comments
    // create iterator

    std::vector<CommentInfo*>::iterator del = m_comments -> begin();
    for(del; del < m_comments -> end(); ++del) 
    {
	delete *del;
	*del = 0;	// delete comment and set pointer to NULL
    }

}
void CommentsBoard::RefreshCommentList()
{
    std::vector<CommentInfo*>::iterator it = m_comments -> begin();
    for(it; it < m_comments -> end(); ++it)
    {
	CommentRect* comment_rect = new CommentRect(m_comments_pane, *it);
	m_comments_v_sizer -> Add(comment_rect, 0, wxEXPAND|wxALL, 0);
    }
    m_comments_pane -> Layout();
}


void CommentsBoard::OnFeedFetched(wxCommandEvent& event)
{
    m_v_sizer -> Clear(true);	// delete the comment rects from the comments panel
    // display the comments
    RefreshCommentList();

    event.Skip();
}

void CommentsBoard::FetchCommentsFeed()
{

    if(m_current_vid)
    {
	wxString* video_id = new wxString(m_current_vid -> getId().c_str(), wxConvUTF8); // get video id
	// we must create the wxString on the heap because it must still exist during the thread execution.
	SearchURL* comment_url = new SearchURL(VIDEO_COMMENTS_SEARCH, *video_id);
	XMLFeed* xml_feed = new XMLFeed(comment_url);

	// create callback object
	FetchCommentsCallback* callback = new FetchCommentsCallback(this);
	// create and run the fetcher thread
	FeedFetcherThread* feed_fetch_thread = new FeedFetcherThread(xml_feed, callback);
	feed_fetch_thread -> Create();

	feed_fetch_thread -> Run();
    }
}

CommentsBoard::CommentRect::CommentRect(wxWindow* parent, CommentInfo* comment, wxWindowID id)
    :wxPanel(parent, id), m_v_sizer(0), m_comment_txt(0), m_comment_info(comment)
{

    m_v_sizer = new wxBoxSizer(wxVERTICAL);

    m_comment_txt = new wxStaticText(this, wxID_ANY, wxString(m_comment_info -> getContent().c_str(), wxConvUTF8));
    m_v_sizer -> Add(m_comment_txt, 0, wxALL | wxEXPAND, 0);
    SetSizerAndFit(m_v_sizer);
}

CommentsBoard::CommentRect::~CommentRect()
{
}
std::vector<CommentInfo*>* CommentsBoard::m_comments = new std::vector<CommentInfo*>();
VideoInfo* CommentsBoard::m_current_vid = 0;

BEGIN_EVENT_TABLE(CommentsBoard, wxPanel)
EVT_COMMAND (ON_FEED_FETCHED, wxEVT_COMMAND_TEXT_UPDATED, CommentsBoard::OnFeedFetched)
END_EVENT_TABLE()
