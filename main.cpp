#include <iostream>
#include "./api/SpotifyToken.h"

int main() {
    std::string clientId = "clientid";
    std::string clientCreds = "clientcred";

    SpotifyToken spotifyToken(clientId, clientCreds);

    spotifyToken.setToken();

    std::cout<<spotifyToken.getToken()<<std::endl;

    return 0;
}
