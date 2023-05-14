#include "MainFrame.h"
#include "../api/SpotifyAPI.h"
#include <wx/wx.h>
#include <iostream>


MainFrame::MainFrame(const wxString& title, SpotifyAPI *spotifyApi) : wxFrame(nullptr, wxID_ANY, title) {
    this->spotifyApi = spotifyApi;
    spotifyApi->setToken();

    wxPanel* searchPanel = new wxPanel(this);

    button = new wxButton(searchPanel, wxID_ANY, "Search");
    button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
    button->SetSize(100,35);
    button->SetPosition(wxPoint(305,0));

    textCtrl = new wxTextCtrl(searchPanel, wxID_ANY, "Input song, album or artist name");
    textCtrl->SetSize(300, 35);


}

void MainFrame::OnButtonClicked(wxCommandEvent &) {
    std::string id = textCtrl->GetValue().ToStdString();
    cout<<id<<endl;
    map<string, string> options;
    //options.insert(make_pair("seed_artists", "0iEtIxbK0KxaSlF7G42ZOp"));
    //options.insert(make_pair("limit", "5"));

    Track track = spotifyApi->getTrack(id, options);
    cout<<track.getName()<<endl;
    cout<< " artists:"<<endl;
    for(string a : track.getArtists()){
        cout<<"   - "<<a<<endl;
    }

    cout<<" recommendations:"<<endl;
    for(Track t : track.getRecommendations()){
        cout<<"   - "<<t.getName()<<endl;
    }
}
