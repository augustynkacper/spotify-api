#ifndef SPOTIFY_API_MAINFRAME_H
#define SPOTIFY_API_MAINFRAME_H

#include <wx/wx.h>
#include "../api/SpotifyAPI.h"


class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title, SpotifyAPI *spotifyApi);
private:
    wxTextCtrl* textCtrl;
    wxButton* searchButton;

    wxPanel* resultPanel;
    wxPanel* searchPanel;
    SpotifyAPI *spotifyApi;

    void OnSearchButtonClicked(wxCommandEvent&);
    void OnArtistButtonClicked(wxCommandEvent&);
    void OnTrackButtonClicked(wxCommandEvent&);

    void ShowTrack(Track track);
    void ShowArtist(Artist artist);
    void ShowSearchResults(pair<vector<Artist>, vector<Track>>);

    void ClearResultPanel();
};



#endif //SPOTIFY_API_MAINFRAME_H
