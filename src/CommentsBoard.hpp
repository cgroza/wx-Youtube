#ifndef COMMENTS_BOARD_H
    #define COMMENTS_BOARD_H
#include <wx/wx.h>
#include <vector>
#include <string>
#include "EventManager.hpp"

class CommentsBoard : public wxPanel
{
  /*Dispalys and manages video comments.*/
public:
  CommentsBoard(wxWindow* parent, EventManager* evt_man, wxWindowID id = wxID_ANY);

  class CommentInfo
  {
    CommentInfo(); 		// to be completed
    /*Represent a video comment. Contains the video comment text, and and other information.*/
  };

  class CommentRect : public wxPanel
  {
    /*Displays and manages controls for a single video comment.*/
    CommentRect(wxWindow* parent, wxWindowID id = wxID_ANY);
    ~CommentRect();
  };
protected:
  wxBoxSizer* m_v_sizer;
  wxPanel* m_comments_pane;
  wxTextCtrl* m_comment_txt;
  std::vector<CommentInfo*>* m_comments;
  
private:
};
#endif  // COMMENTS_BOARD_H
