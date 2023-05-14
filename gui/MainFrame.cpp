#include "MainFrame.h"
#include "../api/SpotifyAPI.h"
#include <wx/wx.h>
#include <wx/statbmp.h>
#include <wx/wxhtml.h>
#include <wx/sizer.h>
#include <iostream>
#include "wx/url.h"
#include <wx/mstream.h>
#include <wx/mediactrl.h>

MainFrame::MainFrame(const wxString& title, SpotifyAPI *spotifyApi) : wxFrame(nullptr, wxID_ANY, title) {
    this->spotifyApi = spotifyApi;
    spotifyApi->setToken();

    searchPanel = new wxPanel(this);
    resultPanel = new wxPanel(this);

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

    pair<vector<Artist>, vector<Track>> result = spotifyApi->search(options);

    ShowSearchResults(result);
}



void MainFrame::ShowTrack(Track track) {
    ClearResultPanel();

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxFont font(wxFontInfo(20).Family(wxFONTFAMILY_DEFAULT).FaceName("Arial").Bold());

    //Artist Name
    wxStaticText* nameLabel = new wxStaticText(resultPanel, wxID_ANY, track.getName(), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    nameLabel->SetFont(font);
    sizer->Add(nameLabel);


    string artists = "";
    int i=0;
    for(string artist : track.getArtists()){
        artists += artist;
        if (i+1==track.getArtists().size()){
            break;
        }
        artists+=", ";
        i += 1;
    }

    wxStaticText* artistsLabel = new wxStaticText(resultPanel, wxID_ANY, artists);
    sizer->Add(artistsLabel);

    // Popularity
    wxString popularityText = wxString::Format("Popularity: %d", track.getPopularity());
    wxStaticText* popularityLabel = new wxStaticText(resultPanel, wxID_ANY, popularityText);
    sizer->Add(popularityLabel);

    resultPanel->SetSizerAndFit(sizer);
    resultPanel->Layout();
}



void MainFrame::ShowSearchResults(pair<vector<Artist>, vector<Track>> result) {

    ClearResultPanel();

    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* artistHeader = new wxStaticText(resultPanel, wxID_ANY, "Found artists:");
    artistHeader->SetFont(font);
    sizer->Add(artistHeader);

    for (Artist artist : result.first){
        wxButton* btn = new wxButton(resultPanel, wxID_ANY, artist.getName());
        btn->SetClientData(new Artist(artist));
        btn->Bind(wxEVT_BUTTON, &MainFrame::OnArtistButtonClicked, this);
        sizer->Add(btn, 0, wxBOTTOM, 3);
    }

    wxStaticText* tracksHeader = new wxStaticText(resultPanel, wxID_ANY, "Found tracks:");
    tracksHeader->SetFont(font);
    sizer->Add(tracksHeader);

    for (Track track : result.second){
        wxButton* btn = new wxButton(resultPanel, wxID_ANY, track.getName());
        btn->SetClientData(new Track(track));
        btn->Bind(wxEVT_BUTTON, &MainFrame::OnTrackButtonClicked, this);
        sizer->Add(btn, 0, wxBOTTOM, 3);
    }


    resultPanel->SetSizerAndFit(sizer);

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

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxFont font(wxFontInfo(20).Family(wxFONTFAMILY_DEFAULT).FaceName("Arial").Bold());

    //Artist Name
    wxStaticText* nameLabel = new wxStaticText(resultPanel, wxID_ANY, artist.getName());
    nameLabel->SetFont(font);
    sizer->Add(nameLabel);

    // Followers
    wxString followersText = wxString::Format("Followers: %d", artist.getFollowers());
    wxStaticText* followersLabel = new wxStaticText(resultPanel, wxID_ANY, followersText);
    sizer->Add(followersLabel);

    // Popularity
    wxString popularityText = wxString::Format("Popularity: %d", artist.getPopularity());
    wxStaticText* popularityLabel = new wxStaticText(resultPanel, wxID_ANY, popularityText);
    sizer->Add(popularityLabel);

    //cout<<artist.getTopTracks().size()<<endl;
    for(Track track : artist.getTopTracks()){
        wxButton* btn = new wxButton(resultPanel, wxID_ANY, track.getName());
        btn->SetClientData(new Track(track));
        btn->Bind(wxEVT_BUTTON, &MainFrame::OnTrackButtonClicked, this);
        sizer->Add(btn);
    }

    resultPanel->SetSizerAndFit(sizer);
    resultPanel->Layout();
}

void MainFrame::OnArtistButtonClicked(wxCommandEvent &event) {
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());

    if ( button ) {
        Artist *artist = (Artist*) button->GetClientData();
        MainFrame::ShowArtist(*artist);
    }
}

void MainFrame::OnTrackButtonClicked(wxCommandEvent &event) {
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if ( button ) {
        Track *track = (Track*) button->GetClientData();
        MainFrame::ShowTrack(*track);
    }
}

/*
    wxBitmap bitmap;
    wxURL urlObj(artist.getImgUrl());
    if (urlObj.GetError() == wxURL_NOERR) {
        wxMemoryOutputStream outputStream;
        if (urlObj.GetInputStream()->IsOk()) {
            urlObj.GetInputStream()->Read(outputStream);
        }

        wxMemoryInputStream inputStream(outputStream.GetOutputStreamBuffer(), outputStream.GetSize());
        wxImage image;
        if (image.LoadFile(inputStream)) {
            bitmap = wxBitmap(image);
            wxStaticBitmap* staticBitmap = new wxStaticBitmap(artistPanel, wxID_ANY, bitmap);
        }
    }
    */
