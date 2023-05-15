#include "Track.h"
#include <iostream>

Track::Track(nlohmann::json j) {
    this->name = j["name"];
    this->popularity = j["popularity"];
    this->duration = j["duration_ms"];
    this->imgUrl = j["album"]["images"][0]["url"];
    this->id = j["id"];

    for(nlohmann::json artist : j["artists"]){
        artists.push_back(artist["name"]);
    }
}

void Track::setSongsRecommendations(nlohmann::json json) {
    for(nlohmann::json j : json["tracks"]) {
        recommendations.push_back(Track(j));
    }
}

Track::Track(const Track &other) {
    name = other.getName();
    popularity = other.getPopularity();
    duration = other.getDuration();
    imgUrl = other.getImgUrl();
    id = other.getId();
    recommendations = other.getRecommendations();
    artists = other.getArtists();
}

