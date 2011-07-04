#include "CommentsBoard.hpp"

CommentsBoard::CommentsBoard(wxWindow* parent, EventManager* evt_man, wxWindowID id): wxPanel(parent), m_v_sizer(0),
							       m_comments_pane(0), m_comments(0)
{
  m_v_sizer = new wxBoxSizer(wxVERTICAL);
  m_comments_pane = new wxPanel(this);
  m_comment_txt = new wxTextCtrl(this, wxID_ANY);

  m_comments = new std::vector<CommentInfo*>();

  m_v_sizer -> Add(m_comments_pane, 3, wxEXPAND | wxALL, 0);
  m_v_sizer -> Add(m_comment_txt, 1, wxEXPAND | wxALL, 0);
  SetSizerAndFit(m_v_sizer);
}

void CommentsBoard::FetchCommentsFeed()
{
    
}

CommentsBoard::CommentRect::CommentRect(wxWindow* parent, CommentInfo* comment, wxWindowID id)
    :wxPanel(parent, id), m_v_sizer(0), m_comment_txt(0), m_comment_info(comment)
{
    m_v_sizer = new wxBoxSizer(wxVERTICAL);
    m_comment_txt = new wxStaticText(this, wxID_ANY, wxT(""));
    m_v_sizer -> Add(m_comment_txt, 3, wxALL | wxEXPAND, 0);
    SetSizerAndFit(m_v_sizer);
}

CommentsBoard::CommentRect::~CommentRect()
{
}
