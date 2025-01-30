#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <memory>
#include <string>
#include "song.h"

using namespace std;

template <typename GenreType, typename ArtistType>
class Playlist
{
private:
    string name;
    vector<shared_ptr<Song<GenreType, ArtistType>>> songs;

public:
    Playlist(const string &name);
    void addSong(const shared_ptr<Song<GenreType, ArtistType>> &song);
    void removeSong(const shared_ptr<Song<GenreType, ArtistType>> &song);
    void showSongs() const;
    string getName() const;
    const vector<shared_ptr<Song<GenreType, ArtistType>>> &getSongs() const;
    static void createPlaylist(vector<Playlist<GenreType, ArtistType>> &playlists, const vector<shared_ptr<Song<GenreType, ArtistType>>> &availableSongs);

    // operator overloading (+ pt. add si - pt. remove)
    Playlist<GenreType, ArtistType> operator+(const shared_ptr<Song<GenreType, ArtistType>> &song);
    Playlist<GenreType, ArtistType> operator-(const shared_ptr<Song<GenreType, ArtistType>> &song);
};

#endif