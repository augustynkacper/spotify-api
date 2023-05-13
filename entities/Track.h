
#ifndef SPOTIFY_API_TRACK_H
#define SPOTIFY_API_TRACK_H

#include <string>
#include "../api/json.hpp"

using namespace std;

class Track {
private:
    string name;

    string id;
    string imgUrl;

    int popularity;
    int duration;

public:

    Track(nlohmann::json);

    [[nodiscard]] string getName() const { return name; }
    [[nodiscard]] string getImgUrl() const { return imgUrl; }
    [[nodiscard]] int getDuration() const { return duration; }
    [[nodiscard]] int getPopularity() const { return popularity; }
    [[nodiscard]] string getId() const { return id; }

};


#endif //SPOTIFY_API_TRACK_H
