#include <curl/curl.h>
#include <iostream>
#include "SpotifyToken.h"

#include "json.hpp"

using json = nlohmann::json;

using namespace std;
SpotifyToken::SpotifyToken(string id, string creds){
    this->clientId = std::move(id);
    this->clientCreds = std::move(creds);
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

void SpotifyToken::setToken() {
    string url = "https://accounts.spotify.com/api/token";
    string header = "Content-Type: application/x-www-form-urlencoded";
    string data = "grant_type=client_credentials&client_id="+clientId+"&client_secret="+clientCreds;

    CURL* curl;

    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl){
        // URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // HEADERS
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        //DATA
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // RESPONSE
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        json j = json::parse(response);
        token = j["access_token"];
    }
}
