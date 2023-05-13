#include <curl/curl.h>
#include <iostream>
#include "SpotifyAPI.h"

#include "../json.hpp"
#include "../entities/Artist.h"
#include "../entities/Album.h"
#include "../entities/Track.h"

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

json SpotifyAPI::request(const string endpoint, const map<string,string> options=map<string,string>(), const string data="") {
    CURL* curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    string response;
    string tmpurl = url + endpoint;

    if ( !options.empty() ){
        tmpurl += "?";
        for(const auto& pair : options)
            tmpurl += pair.first + "=" + pair.second + "&";
    }

    if (curl) {

        // URL
        curl_easy_setopt(curl, CURLOPT_URL, tmpurl.c_str());

        // HEADERS
        if ( !token.empty() ){
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, header.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        // DATA (only if token isn't initialized)
        else if ( !data.empty() ){
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

    json j = request("/api/token", map<string,string>(), data);

    // update token, url, header when token received
    token = j["access_token"];
    url = "https://api.spotify.com";
    header = "Authorization: Bearer " + token;

    cout<<token<<endl;
}

Album SpotifyAPI::getAlbum(const std::string id) {
    nlohmann::json json = request("/v1/albums/" + id);
    return Album(json);
}

Artist SpotifyAPI::getArtist(const std::string id) {
    nlohmann::json json = request("/v1/artists/" + id);
    Artist artist = Artist(json);
    json = SpotifyAPI::getArtistTopTracks(id);
    artist.setTopTracks(json);
    return artist;
}

Track SpotifyAPI::getTrack(const std::string id, const map<string,string> options) {
    nlohmann::json json = request("/v1/tracks/" + id);

    Track track(json);

    json = getSongsRecommendations(options);
    track.setSongsRecommendations(json);

    return track;
}

nlohmann::json SpotifyAPI::getArtistTopTracks(const std::string id) {
    return request("/v1/artists/" + id + "/top-tracks?country=PL");
}

nlohmann::json SpotifyAPI::getSongsRecommendations(std::map<std::string, std::string> options) {
    return request("/v1/recommendations", options);;
}

//vector<Track> SpotifyAPI::getSongsRecommendations(std::map<std::string, std::string>) {
//    return request("/v1/recommendations", "");
//}

