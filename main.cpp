#include <iostream>

#include "./api/SpotifyAPI.h"
#include "entities/Artist.h"
#include "entities/Track.h"
#include "entities/Album.h"



using namespace std;

int main() {
    std::string clientId = "";
    std::string clientCreds = "";

    SpotifyAPI spotifyAPI(clientId, clientCreds);
    spotifyAPI.setToken();

    map<string, string> options;
    options.insert(make_pair("seed_artists", "0iEtIxbK0KxaSlF7G42ZOp"));
    options.insert(make_pair("seed_tracks", "0vjeOZ3Ft5jvAi9SBFJm1j"));
    options.insert(make_pair("limit", "5"));

    Track track = spotifyAPI.getTrack("2dHHgzDwk4BJdRwy9uXhTO", options);
    cout<<track.getName()<<endl;
    cout<< " artists:"<<endl;
    for(string a : track.getArtists()){
        cout<<"   - "<<a<<endl;
    }

    cout<<" recommendations:"<<endl;
    for(Track t : track.getRecommendations()){
        cout<<"   - "<<t.getName()<<endl;
    }
    //nlohmann::json j = spotifyAPI.getSongsRecommendations(options);
    //cout<<j.dump(3);

    return 0;
}
