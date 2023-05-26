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

#include "../json.hpp"

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
std::string parse(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (c == ' ')
            result += "%20";
        else
            result += c;
    }
    return result;
}
void MainFrame::OnSearchButtonClicked(wxCommandEvent &) {
    std::string input = textCtrl->GetValue().ToStdString();
    input = parse(input);

    std::cout<<input<<std::endl;

    map<string, string> options;
    options.insert(make_pair("q", input));
    options.insert(make_pair("type", "artist,track"));
    options.insert(make_pair("limit", "5"));

    pair<vector<Artist>, vector<Track>> result = spotifyApi->search(options);

    ShowSearchResults(result);
}

string join(vector<string> vec){
    string artists = "";
    int i=0;
    for(string artist : vec){
        artists += artist;
        if (i+1 == vec.size())
            break;
        artists+=", ";
        i += 1;
    }
    return artists;
}


void MainFrame::ShowTrack(Track track) {
    ClearResultPanel();

    map<string, string> options;
    options.insert(make_pair("seed_tracks", track.getId()));
    options.insert(make_pair("limit", "5"));
    nlohmann::json j = spotifyApi->getSongsRecommendations(options);
    track.setSongsRecommendations(j);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxFont font(wxFontInfo(20).Family(wxFONTFAMILY_DEFAULT).FaceName("Arial").Bold());

    //Artist Name
    wxStaticText* nameLabel = new wxStaticText(resultPanel, wxID_ANY, track.getName(), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    nameLabel->SetFont(font);
    sizer->Add(nameLabel, 0, wxLEFT, 20);

    string artists = join(track.getArtists());
    wxStaticText* artistsLabel = new wxStaticText(resultPanel, wxID_ANY, artists);
    sizer->Add(artistsLabel, 0, wxLEFT, 25);

    // Popularity
    wxString popularityText = wxString::Format("Popularity: %d", track.getPopularity());
    wxStaticText* popularityLabel = new wxStaticText(resultPanel, wxID_ANY, popularityText);
    sizer->Add(popularityLabel, 0, wxLEFT | wxBOTTOM, 25);

    for(Track t : track.getRecommendations()){
        MainFrame::ShowTrackLink(t, sizer);
    }

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
        MainFrame::ShowArtistLink(artist, sizer);
    }

    wxStaticText* tracksHeader = new wxStaticText(resultPanel, wxID_ANY, "Found tracks:");
    tracksHeader->SetFont(font);
    sizer->Add(tracksHeader, 0, wxLEFT | wxTOP, 20);

    for (Track track : result.second){
        MainFrame::ShowTrackLink(track, sizer);
    }

    resultPanel->SetSizerAndFit(sizer);

    resultPanel->Layout();
}

void MainFrame::ShowArtist(Artist artist) {
    ClearResultPanel();
    nlohmann::json j = spotifyApi->getArtistTopTracks(artist.getId());
    artist.setTopTracks(j);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxFont font(wxFontInfo(23).Family(wxFONTFAMILY_DEFAULT).FaceName("Arial").Bold());

    //Artist Name
    wxStaticText* nameLabel = new wxStaticText(resultPanel, wxID_ANY, artist.getName());
    nameLabel->SetFont(font);
    sizer->Add(nameLabel, 0, wxLEFT, 20);

    // Followers
    wxString followersText = wxString::Format("Followers: %d", artist.getFollowers());
    wxStaticText* followersLabel = new wxStaticText(resultPanel, wxID_ANY, followersText);
    sizer->Add(followersLabel, 0, wxLEFT, 25);

    // Popularity
    wxString popularityText = wxString::Format("Popularity: %d", artist.getPopularity());
    wxStaticText* popularityLabel = new wxStaticText(resultPanel, wxID_ANY, popularityText);
    sizer->Add(popularityLabel, 0, wxLEFT | wxBOTTOM, 25);

    //cout<<artist.getTopTracks().size()<<endl;
    for(Track track : artist.getTopTracks()){
        MainFrame::ShowTrackLink(track, sizer);
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

// ---------------------------------------------------
// ------------- ARTIST AND TRACK LINKS --------------
// ---------------------------------------------------

void MainFrame::OnArtistClicked(wxMouseEvent &event) {
    wxPanel* button = dynamic_cast<wxPanel*>(event.GetEventObject());

    if ( button ) {
        Artist *artist = (Artist*) button->GetClientData();
        MainFrame::ShowArtist(*artist);
    }
}

void MainFrame::OnTrackClicked(wxMouseEvent& event) {
    wxPanel* button = dynamic_cast<wxPanel*>(event.GetEventObject());
    if ( button ) {
        Track *track = (Track*) button->GetClientData();
        MainFrame::ShowTrack(*track);
    }
}

void MainFrame::ShowTrackLink(Track track, wxBoxSizer *sizer) {
    wxPanel* panel = new wxPanel(resultPanel);
    wxBoxSizer* trackSizer = new wxBoxSizer(wxVERTICAL);

    wxFont font(wxFontInfo(12).Family(wxFONTFAMILY_DEFAULT).FaceName("Arial").Bold());

    wxStaticText* name = new wxStaticText(panel, wxID_ANY, track.getName(), wxDefaultPosition, wxDefaultSize);
    name->SetFont(font);
    name->SetMinSize(wxSize(600,name->GetSize().GetY()));
    trackSizer->Add(name, 1, wxLEFT | wxTOP, 5);

    string a = join(track.getArtists());
    wxStaticText* artists = new wxStaticText(panel, wxID_ANY, a);
    trackSizer->Add(artists, 1, wxLEFT | wxBOTTOM, 7);

    panel->SetBackgroundColour("#252525");
    panel->SetSizerAndFit(trackSizer);

    panel->SetClientData(new Track(track));
    panel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnTrackClicked, this);

    sizer->Add(panel, 0, wxBOTTOM | wxLEFT, 5);
}

void MainFrame::ShowArtistLink(Artist artist, wxBoxSizer *sizer) {
    wxPanel* panel = new wxPanel(resultPanel);
    wxBoxSizer* artistSizer = new wxBoxSizer(wxHORIZONTAL);

    wxFont font(wxFontInfo(12).Family(wxFONTFAMILY_DEFAULT).FaceName("Arial").Bold());

    wxStaticText* name = new wxStaticText(panel, wxID_ANY, artist.getName(), wxDefaultPosition, wxDefaultSize);
    name->SetFont(font);
    name->SetMinSize(wxSize(200,name->GetSize().GetY()));
    artistSizer->Add(name, 1, wxALL, 7);

    wxStaticText* followers = new wxStaticText(panel, wxID_ANY, "Followers: "+std::to_string(artist.getFollowers()));
    artistSizer->Add(followers, 1, wxLEFT | wxBOTTOM, 7);
    followers->SetMaxSize(followers->GetSize());


    panel->SetBackgroundColour("#252525");
    panel->SetSizerAndFit(artistSizer);

    panel->SetClientData(new Artist(artist));
    panel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnArtistClicked, this);

    sizer->Add(panel, 0, wxBOTTOM | wxLEFT, 5);
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
