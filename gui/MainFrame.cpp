#include "MainFrame.h"
#include "../api/SpotifyAPI.h"
#include <wx/wx.h>
#include <iostream>


MainFrame::MainFrame(const wxString& title, SpotifyAPI *spotifyApi) : wxFrame(nullptr, wxID_ANY, title) {
    this->spotifyApi = spotifyApi;
    spotifyApi->setToken();

    searchPanel = new wxPanel(this);
    resultPanel = new wxPanel(this);

    resultPanel->SetBackgroundColour(wxColour("blue"));

    // search button and text input
    searchButton = new wxButton(searchPanel, wxID_ANY, "Search", wxDefaultPosition, wxSize(100, 35));
    searchButton->Bind(wxEVT_BUTTON, &MainFrame::OnSearchButtonClicked, this);
    textCtrl = new wxTextCtrl(searchPanel, wxID_ANY, "future", wxDefaultPosition, wxSize(100, 35));

    // sizer for displaying text input and search button horizontally
    wxBoxSizer* searchSizer = new wxBoxSizer(wxHORIZONTAL);
    searchSizer->Add(textCtrl, 1, wxALL, 10);
    searchSizer->Add(searchButton, 0, wxALL, 10 );
    searchPanel->SetSizerAndFit(searchSizer);


    // sizer for whole frame
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(searchPanel, 0, wxEXPAND | wxALL, 10);
    sizer->Add(resultPanel, 1, wxEXPAND);
    this->SetSizerAndFit(sizer);
}

void MainFrame::OnSearchButtonClicked(wxCommandEvent &) {
    std::string input = textCtrl->GetValue().ToStdString();

    map<string, string> options;
    options.insert(make_pair("q", input));
    options.insert(make_pair("type", "artist,track"));
    options.insert(make_pair("limit", "5"));
    cout<<"essa1"<<endl;
    pair<vector<Artist>, vector<Track>> result = spotifyApi->search(options);

    ShowSearchResults(result);
}



void MainFrame::ShowTrack(Track track) {
    ClearResultPanel();
    wxStaticText* textField = new wxStaticText(resultPanel, wxID_ANY, track.getName());
    resultPanel->Layout();
}



void MainFrame::ShowSearchResults(pair<vector<Artist>, vector<Track>> result) {

    ClearResultPanel();

    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxPanel* artistPanel = new wxPanel(resultPanel);
    wxBoxSizer* artistsSizer = new wxBoxSizer(wxVERTICAL);
    artistPanel->SetBackgroundColour(wxColour("red"));
    wxStaticText* artistHeader = new wxStaticText(artistPanel, wxID_ANY, "Found artists:");
    if (font.IsOk())
        artistHeader->SetFont(font);
    artistsSizer->Add(artistHeader);

    for (Artist artist : result.first){
        wxButton* btn = new wxButton(artistPanel, wxID_ANY, artist.getName());
        btn->SetClientData(new Artist(artist));
        btn->Bind(wxEVT_BUTTON, &MainFrame::OnArtistButtonClicked, this);
        artistsSizer->Add(btn);
    }
    artistPanel->SetSizerAndFit(artistsSizer);

    resultPanel->Layout();
}

void MainFrame::ClearResultPanel() {
    resultPanel->Freeze();
    resultPanel->DestroyChildren();
    resultPanel->Layout();
    resultPanel->Thaw();
}

void MainFrame::ShowArtist(Artist artist) {
    ClearResultPanel();
    cout<<"entered artist panel"<<endl;
    wxPanel* artistPanel = new wxPanel(resultPanel);
    cout<<"panel created"<<endl;
    wxStaticText* artistHeader = new wxStaticText(artistPanel, wxID_ANY, artist.getName());
    cout<<"text created"<<endl;
    artistPanel->Layout();
    cout<<"artist panel updated"<<endl;
    resultPanel->Layout();
}

void MainFrame::OnArtistButtonClicked(wxCommandEvent &event) {
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());

    if ( button ) {
        Artist *artist = (Artist*) button->GetClientData();
        cout<<"artist caste"<<endl;
        cout<<artist->getId()<<endl;
        MainFrame::ShowArtist(*artist);
    }
}

void MainFrame::OnTrackButtonClicked(wxCommandEvent &) {

}
