#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <memory>
#include <string>
#include "song.h"

using namespace std;

template <typename GenreType, typename ArtistType>
class Playlist {
private:
    string name;
    vector<shared_ptr<Song<GenreType, ArtistType>>> songs;

public:
    Playlist(const string& name);
    void addSong(const shared_ptr<Song<GenreType, ArtistType>>& song);
    void showSongs() const;
    string getName() const;
};

#endif
