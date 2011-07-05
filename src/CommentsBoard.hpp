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



class CommentsBoard : public wxPanel
{
  /*Dispalys and manages video comments.*/
public:
  CommentsBoard(wxWindow* parent, EventManager* evt_man, wxWindowID id = wxID_ANY);

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
      VideoInfo* m_current_vid;
  };
protected:
  wxBoxSizer* m_v_sizer;
  wxPanel* m_comments_pane;
  wxTextCtrl* m_comment_txt;
  std::vector<CommentInfo*>* m_comments;
  
private:
    void FetchCommentsFeed();//populates the m_comments
};
#endif  // COMMENTS_BOARD_H
