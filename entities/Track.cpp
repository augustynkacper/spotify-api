#include "Track.h"

Track::Track(nlohmann::json j) {
    this->name = j["name"];
    this->popularity = j["popularity"];
    this->duration = j["duration_ms"];
    this->imgUrl = j["album"]["images"][0]["url"];
    this->id = j["id"];
}