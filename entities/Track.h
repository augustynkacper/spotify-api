
#ifndef SPOTIFY_API_TRACK_H
#define SPOTIFY_API_TRACK_H

#include <string>
#include "../json.hpp"

using namespace std;

class Track {
private:
    string name;

    string id;
    string imgUrl;
    vector<string> artists;
    vector<Track> recommendations;

    int popularity;
    int duration;

public:

    Track(nlohmann::json);

    void setSongsRecommendations( nlohmann::json);

    [[nodiscard]] string getName() const { return name; }
    [[nodiscard]] string getImgUrl() const { return imgUrl; }
    [[nodiscard]] int getDuration() const { return duration; }
    [[nodiscard]] int getPopularity() const { return popularity; }
    [[nodiscard]] string getId() const { return id; }
    [[nodiscard]] vector<string> getArtists() const { return artists; }
    [[nodiscard]] const vector<Track> getRecommendations() const { return recommendations; }
};


#endif //SPOTIFY_API_TRACK_H
