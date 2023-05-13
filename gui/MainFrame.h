#ifndef SPOTIFY_API_MAINFRAME_H
#define SPOTIFY_API_MAINFRAME_H

#include <wx/wx.h>


class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);
private:
    wxTextCtrl* textCtrl;
    wxButton* button;

    void OnButtonClicked(wxCommandEvent&);
};



#endif //SPOTIFY_API_MAINFRAME_H
