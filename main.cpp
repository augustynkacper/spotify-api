#include <iostream>
#include "./api/SpotifyAPI.h"

#include "./api/json.hpp"

int main() {
    std::string clientId = "id";
    std::string clientCreds = "credidentials";

    SpotifyAPI spotifyAPI(clientId, clientCreds);

    spotifyAPI.setToken();

    // get data
    std::string endpoint = "/v1/artists/2feDdbD5araYcm6JhFHHw7";

    nlohmann::json j = spotifyAPI.request(endpoint, "");
    std::cout << j;

    return 0;
}
