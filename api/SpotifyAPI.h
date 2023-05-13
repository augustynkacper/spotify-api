#ifndef SPOTIFY_API_SPOTIFYAPI_H
#define SPOTIFY_API_SPOTIFYAPI_H

#include "../json.hpp"
#include "../entities/Album.h"
#include "../entities/Artist.h"
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

    nlohmann::json request(const std::string endpoint, const map<string,string>, const std::string data);

    Album getAlbum(const std::string);
    Artist getArtist(const std::string);
    Track getTrack(const string, const map<string,string>);

    nlohmann::json getArtistTopTracks(const std::string);
    nlohmann::json getSongsRecommendations(map<string, string>);
};


#endif //SPOTIFY_API_SPOTIFYAPI_H
