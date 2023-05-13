#include <curl/curl.h>
#include <iostream>
#include "SpotifyAPI.h"

#include "json.hpp"

using json = nlohmann::json;

using namespace std;

SpotifyAPI::SpotifyAPI(string id, string creds){
    this->clientId = std::move(id);
    this->clientCreds = std::move(creds);
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

json SpotifyAPI::request(const string endpoint, const string data, const string request) {
    CURL* curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    string response;

    string tmpurl = url + endpoint;

    if (curl) {
        //curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request.c_str());

        // URL
        curl_easy_setopt(curl, CURLOPT_URL, tmpurl.c_str());

        // HEADERS
        if ( !token.empty() ){
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, header.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        //DATA
        if ( !data.empty() ){
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        }

        // RESPONSE
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);


    }
    if (response.empty()){
        return nlohmann::json();
    }
    return json::parse(response);
    return NULL;
}

void SpotifyAPI::setToken() {
    string data = "grant_type=client_credentials&client_id="+clientId+"&client_secret="+clientCreds;

    json j = request("/api/token", data, "GET");

    // update token, url, header when token received
    token = j["access_token"];
    url = "https://api.spotify.com";
    header = "Authorization: Bearer " + token;
}

nlohmann::json SpotifyAPI::getAlbum(const std::string id) {
    return request("/v1/albums/" + id, "", "GET");
}

nlohmann::json SpotifyAPI::getArtist(const std::string id) {
    return request("/v1/artists/" + id, "", "GET");
}

nlohmann::json SpotifyAPI::getTrack(const std::string id) {
    return request("/v1/tracks/" + id, "", "GET");
}

nlohmann::json SpotifyAPI::getArtistTopTracks(const std::string id) {
    return request("/v1/artists/" + id + "/top-tracks?country=PL", "", "GET");
}

