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
    options.insert(make_pair("q", "rodowicz"));
    options.insert(make_pair("type", "artist,track"));
    options.insert(make_pair("limit", "5"));

    pair<vector<Artist>, vector<Track>> result = spotifyAPI.search(options);


    return 0;
}
