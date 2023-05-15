#include "Artist.h"

Artist::Artist(nlohmann::json j) {
    name = j["name"];
    popularity = j["popularity"];
    if (j["images"].size()>0){
        imgUrl = j["images"][0]["url"];
    }
    id = j["id"];
    genres = j["genres"];
    followers = j["followers"]["total"];
}

void Artist::setTopTracks(nlohmann::json j) {
    for (nlohmann::json &trackJSON : j["tracks"]){
        Track track(trackJSON);
        topTracks.push_back(track);
    }
}

Artist::Artist(const Artist &other) {
    name = other.getName();
    id = other.getId();
    imgUrl = other.getImgUrl();
    popularity = other.getPopularity();
    followers = other.getFollowers();
    topTracks = other.getTopTracks();
    genres = other.getGenres();
}

