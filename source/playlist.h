#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <memory>
#include "song.h"

using namespace std;

template <typename GenreType, typename ArtistType>
class Playlist {
private:
    vector<shared_ptr<Song<GenreType, ArtistType>>> songs;

public:
    void addSong(const shared_ptr<Song<GenreType, ArtistType>>& song);
    void removeSong(const string& title);
    void showSongs() const;
    void playAll() const;
    void pauseAll() const;
    void stopAll() const;
};

#endif
