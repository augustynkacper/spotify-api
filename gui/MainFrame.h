#ifndef SPOTIFY_API_MAINFRAME_H
#define SPOTIFY_API_MAINFRAME_H

#include <wx/wx.h>
#include "../api/SpotifyAPI.h"


class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title, SpotifyAPI *spotifyApi);
private:
    wxTextCtrl* textCtrl;
    wxButton* button;
    SpotifyAPI *spotifyApi;

    void OnButtonClicked(wxCommandEvent&);
};



#endif //SPOTIFY_API_MAINFRAME_H
