//
// Created by kaacpier on 13.05.23.
//

#ifndef SPOTIFY_API_ARTIST_H
#define SPOTIFY_API_ARTIST_H

#include <string>
#include <vector>
#include "Track.h"

using namespace std;

class Artist {
private:
    string name;
    string id;

    string imgUrl;
    vector<Track> topTracks;
    vector<string> genres;

    int popularity;
    int followers;

public:
    Artist(nlohmann::json);

    string getName() const { return name; }
    string getId() const { return id; }
    string getImgUrl() const { return imgUrl; }
    vector<Track> getTopTracks() const { return topTracks; }
    vector<string> getGenres() const { return genres; }
    int getPopularity() const { return popularity; }
    int getFollowers() const { return followers; }

    void setTopTracks(nlohmann::json);

};


#endif //SPOTIFY_API_ARTIST_H
