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
