#include <iostream>
#include "./api/SpotifyAPI.h"

#include "./api/json.hpp"

int main() {
    std::string clientId = "";
    std::string clientCreds = "";

    SpotifyAPI spotifyAPI(clientId, clientCreds);

    spotifyAPI.setToken();

    // get data
    nlohmann::json j = spotifyAPI.getTrack("4Cus7EuLI1pdrdbJz0dnFa");

    std::cout << j.dump(4) << std::endl;

    return 0;
}
