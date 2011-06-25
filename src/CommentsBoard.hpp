#ifndef COMMENTS_BOARD_H
    #define COMMENTS_BOARD_H
#include <wx/panel.h>

class CommentsBoard : public wxPanel
{
  /*Dispalys and manages video comments.*/
public:
  CommentsBoard(wxWindow* parent, wxWindowID id = wxID_ANY);
  ~CommentsBoard();

  class CommentInfo
  {
    CommentInfo(); 		// to be completed
    /*Represent a video comment. Contains the video comment text, and and other information.*/
  };

  class CommentPane : public wxPanel
  {
    /*Displays and manages controls for a single video comment.*/
    CommentPane(wxWindow* parent, wxWindowID id = wxID_ANY);
    ~CommentPane();
  };
protected:

private:
};
#endif  // COMMENTS_BOARD_H
