#include <wx/wx.h>
#include "MainFrame.h"
#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("SpotifyAPI", spotifyApi);
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}

App::App() {
    std::string clientId = "1b4db4f55bd94081b6c02f47becb3b2f";
    std::string clientCreds = "517070415c5540019ad22c282f88d907";
    spotifyApi = new SpotifyAPI(clientId, clientCreds);
}


