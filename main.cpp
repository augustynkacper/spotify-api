#include <iostream>

#include "./api/SpotifyAPI.h"
#include "entities/Artist.h"
#include "entities/Track.h"

using namespace std;

int main() {
    std::string clientId = "1b4db4f55bd94081b6c02f47becb3b2f";
    std::string clientCreds = "517070415c5540019ad22c282f88d907";

    SpotifyAPI spotifyAPI(clientId, clientCreds);
    spotifyAPI.setToken();

    map<string, string> options;
    options.insert(make_pair("q", "future"));
    options.insert(make_pair("type", "artist,track"));
    options.insert(make_pair("limit", "5"));
/*
    std::pair<vector<Artist>, vector<Track>> pair = spotifyAPI.search(options);

    cout<< " artists:"<<endl;
    for(Artist a : pair.first){
        cout<<"   - "<<a.getName()<<endl;
    }

    cout<< " tracks:"<<endl;
    for(Track t : pair.second){
        cout<<"   - "<<t.getName()<<endl;
    }*/



    map<string, string> options2;
    options2.insert(make_pair("seed_artists", "0iEtIxbK0KxaSlF7G42ZOp"));
    options2.insert(make_pair("limit", "5"));
    Track track = spotifyAPI.getTrack("0YFqKxV9uNu6LUeYkLOKRS", options2);

    for (Track t : track.getRecommendations()){
        cout <<t.getName()<<endl;
    }


    return 0;
}
