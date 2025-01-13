#include "playlist.h"
#include <iostream>

// Constructor definition
template <typename GenreType, typename ArtistType>
Playlist<GenreType, ArtistType>::Playlist(const string& name) {
    this->name = name;
}

// Method to add a song to the playlist
template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::addSong(const shared_ptr<Song<GenreType, ArtistType>>& song) {
    songs.push_back(song);
}

// Method to display all songs in the playlist
template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::showSongs() const {
    for (const auto& song : songs) {
        song->songDetails();
        cout << endl;
    }
}

// Method to get the playlist name
template <typename GenreType, typename ArtistType>
string Playlist<GenreType, ArtistType>::getName() const {
    return name;
}

// Explicit template instantiation
template class Playlist<string, string>;
