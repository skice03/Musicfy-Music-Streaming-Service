#include "playlist.h"
#include <algorithm>
#include <iostream>

template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::addSong(const shared_ptr<Song<GenreType, ArtistType>>& song) {
    songs.push_back(song);
}

template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::removeSong(const string& title) {
    auto it = remove_if(songs.begin(), songs.end(),
                        [&title](const shared_ptr<Song<GenreType, ArtistType>>& song) {
                            return song->getTitle() == title;
                        });
    if (it != songs.end()) {
        songs.erase(it, songs.end());
        cout << "Song \"" << title << "\" removed from playlist.\n";
    } else {
        cout << "Song \"" << title << "\" not found in playlist.\n";
    }
}

template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::showSongs() const {
    for (const auto& song : songs) {
        song->songDetails();
        cout << endl;
    }
}

template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::playAll() const {
    for (const auto& song : songs) {
        song->play();
    }
}

template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::pauseAll() const {
    for (const auto& song : songs) {
        song->pause();
    }
}

template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::stopAll() const {
    for (const auto& song : songs) {
        song->stop();
    }
}

// Explicit template instantiation
template class Playlist<string, string>;
