#ifndef SPOTIFY_API_SPOTIFYAPI_H
#define SPOTIFY_API_SPOTIFYAPI_H

#include "json.hpp"
#include <string>

class SpotifyAPI {
private:
    // for getting a token
    std::string clientId;
    std::string clientCreds;

    // for sending requests
    std::string token;
    std::string url = "https://accounts.spotify.com";
    std::string header = "Content-Type: application/x-www-form-urlencoded";

public :
    SpotifyAPI(std::string, std::string);
    void setToken();
    [[nodiscard]] std::string getToken() const { return token; }
    nlohmann::json request(const std::string endpoint, const std::string data);

    nlohmann::json getAlbum(const std::string);
    nlohmann::json getArtist(const std::string);
    nlohmann::json getTrack(const std::string);
};


#endif //SPOTIFY_API_SPOTIFYAPI_H
