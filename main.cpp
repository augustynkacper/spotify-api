#include <iostream>

#include "./api/SpotifyAPI.h"
#include "entities/Artist.h"
#include "entities/Track.h"

using namespace std;

int main() {
    std::string clientId = "";
    std::string clientCreds = "";

    SpotifyAPI spotifyAPI(clientId, clientCreds);
    spotifyAPI.setToken();

    map<string, string> options;
    options.insert(make_pair("q", "future"));
    options.insert(make_pair("type", "artist,track"));
    options.insert(make_pair("limit", "5"));

    std::pair<vector<Artist>, vector<Track>> pair = spotifyAPI.search(options);

    cout<< " artists:"<<endl;
    for(Artist a : pair.first){
        cout<<"   - "<<a.getName()<<endl;
    }

    cout<< " tracks:"<<endl;
    for(Track t : pair.second){
        cout<<"   - "<<t.getName()<<endl;
    }



    /*
    Track track = spotifyAPI.getTrack("0vjeOZ3Ft5jvAi9SBFJm1j", options);
    cout<<track.getName()<<endl;
    cout<< " artists:"<<endl;
    for(string a : track.getArtists()){
        cout<<"   - "<<a<<endl;
    }

    cout<<" recommendations:"<<endl;
    for(Track t : track.getRecommendations()){
        cout<<"   - "<<t.getName()<<endl;
    }
     */

    //nlohmann::json j = spotifyAPI.getSongsRecommendations(options);
    //cout<<j.dump(3);

    return 0;
}
