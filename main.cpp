#include <iostream>
#include "./api/SpotifyAPI.h"

#include "./api/json.hpp"
#include "entities/Artist.h"

#include <future>

using namespace std;

int main() {
    std::string clientId = "";
    std::string clientCreds = "";

    SpotifyAPI spotifyAPI(clientId, clientCreds);

    spotifyAPI.setToken();

    nlohmann::json j = spotifyAPI.getArtist("0iEtIxbK0KxaSlF7G42ZOp");
    Artist artist(j);
    cout<<j.dump(3)<<endl;
    j = spotifyAPI.getArtistTopTracks("0iEtIxbK0KxaSlF7G42ZOp");

    artist.setTopTracks(j);
    cout<<j.dump(3)<<endl;
    for(Track track : artist.getTopTracks()){
        cout<<track.getName()<<endl;
    }

    return 0;
}
