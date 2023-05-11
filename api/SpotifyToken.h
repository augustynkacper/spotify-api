#ifndef SPOTIFY_API_SPOTIFYTOKEN_H
#define SPOTIFY_API_SPOTIFYTOKEN_H

#include <string>

class SpotifyToken {
private:
    std::string token;
    std::string clientId;
    std::string clientCreds;

public :
    SpotifyToken(std::string, std::string);
    void setToken();
    std::string getToken() { return token; }
};


#endif //SPOTIFY_API_SPOTIFYTOKEN_H
