#include "CommentsBoard.hpp"

CommentsBoard::CommentsBoard(wxWindow* parent, EventManager* evt_man, wxWindowID id): wxPanel(parent), m_v_sizer(0),
							      m_comments_pane(0)
{
    // create the event handler an bind it
    on_select = new OnVideoSelect(this);
    evt_man -> BindSelectVideoEvent(on_select);

    m_v_sizer = new wxBoxSizer(wxVERTICAL);

    m_comments_pane = new CommentsPane(this);

   // m_comment_txt = new wxTextCtrl(this, wxID_ANY);
    //m_v_sizer -> Add(m_comments_pane, 4, wxEXPAND | wxALL, 0);
    //m_v_sizer -> Add(m_comment_txt, 1, wxEXPAND | wxALL, 0);
    SetSizerAndFit(m_v_sizer);

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
    m_comments -> clear();
}

void CommentsBoard::OnFeedFetched(wxCommandEvent& event)
{
    // display the comments
    m_comments_pane -> RefreshCommentList();

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

CommentsPane::CommentRect::CommentRect(wxWindow* parent, CommentInfo* comment, wxWindowID id)
    :wxPanel(parent, id), m_v_sizer(0), m_comment_txt(0), m_comment_info(comment)
{

    m_v_sizer = new wxBoxSizer(wxVERTICAL);

    m_comment_txt = new wxTextCtrl(this, wxID_ANY, wxString(m_comment_info -> getContent().c_str(), wxConvUTF8));
    m_v_sizer -> Add(m_comment_txt, 0, wxALL | wxEXPAND, 0);
    SetSizerAndFit(m_v_sizer);
}

CommentsPane::CommentRect::~CommentRect()
{
}

CommentsPane::CommentsPane(CommentsBoard* parent) : wxScrolledWindow(parent), m_v_sizer(0), m_parent(parent)
{
    m_v_sizer = new wxBoxSizer(wxVERTICAL);
    //wxString(m_comment_info -> getContent().c_str(), wxConvUTF8)
    m_comment_txt = new wxTextCtrl(this, wxID_ANY, wxT("Comments"));
    SetSizerAndFit(m_v_sizer);
}


void CommentsPane::AddComment(CommentInfo* comment)
{
    //CommentRect* comment_rect = new CommentRect(this, comment);
    //m_v_sizer -> Add(comment_rect, 1, wxEXPAND|wxALL, 0);
    
    //Fit();
}


void CommentsPane::RefreshCommentList()
{
    m_v_sizer -> Clear(true);	// delete the comment rects from the comments panel
    std::vector<CommentInfo*>::iterator it = m_parent ->  m_comments -> begin();
    for(it; it < m_parent -> m_comments -> end(); ++it)
    {
	//wxString(m_comment_info -> getContent().c_str(), wxConvUTF8)
	m_comment_txt->AppendText(wxString((*it) -> getContent().c_str(), wxConvUTF8));
	//CommentRect* comment_rect = new CommentRect(this, *it);
	m_v_sizer -> Add(m_comment_txt);
    }
    Fit();
}

std::vector<CommentInfo*>* CommentsBoard::m_comments = new std::vector<CommentInfo*>();
VideoInfo* CommentsBoard::m_current_vid = 0;

BEGIN_EVENT_TABLE(CommentsBoard, wxPanel)
EVT_COMMAND (ON_FEED_FETCHED, wxEVT_COMMAND_TEXT_UPDATED, CommentsBoard::OnFeedFetched)
END_EVENT_TABLE()
