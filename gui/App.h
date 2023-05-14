#ifndef SPOTIFY_API_APP_H
#define SPOTIFY_API_APP_H

#include "../api/SpotifyAPI.h"
#include <wx/wx.h>

class App : public wxApp {
private:
    SpotifyAPI *spotifyApi;

public:
    bool OnInit();
    App();
};


#endif //SPOTIFY_API_APP_H
