#include "song.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor definition
template <typename GenreType, typename ArtistType>
Song<GenreType, ArtistType>::Song(const string& title, const ArtistType& artist, const GenreType& genre, float length) {
    this->title = title;
    this->artist = artist;
    this->genre = genre;
    this->length = length;
}

// Method to display song details
template <typename GenreType, typename ArtistType>
void Song<GenreType, ArtistType>::songDetails() const {
    cout << "Song title: " << title << "\nArtist: " << artist << "\nGenre: " << genre << "\nLength: " << length << " minutes\n";
}

// Method to get the song title
template <typename GenreType, typename ArtistType>
string Song<GenreType, ArtistType>::getTitle() const {
    return title;
}

// Method to play the song
template <typename GenreType, typename ArtistType>
void Song<GenreType, ArtistType>::play() const {
    cout << "Now playing: " << title << " by " << artist << endl;
}

// Method to pause the song
template <typename GenreType, typename ArtistType>
void Song<GenreType, ArtistType>::pause() const {
    cout << "Pausing song: " << title << " by " << artist << endl;
}

// Method to stop the song
template <typename GenreType, typename ArtistType>
void Song<GenreType, ArtistType>::stop() const {
    // Intentionally left empty for this example
}

// Destructor
template <typename GenreType, typename ArtistType>
Song<GenreType, ArtistType>::~Song() {}

// Method to load songs from file
template <typename GenreType, typename ArtistType>
bool Song<GenreType, ArtistType>::loadSongsFromFile(const string& filename, vector<shared_ptr<Song<GenreType, ArtistType>>>& songs) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    string line;
    bool fileNotEmpty = false;
    while (getline(file, line)) {
        fileNotEmpty = true;
        stringstream ss(line);
        string title, artist, genre;
        float length;

        // Read song details separated by commas
        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');
        ss >> length;

        songs.push_back(make_shared<Song<GenreType, ArtistType>>(title, artist, genre, length));
    }

    file.close();
    if (!fileNotEmpty) {
        cerr << "File is empty: " << filename << endl;
        return false;
    }

    return true;
}

// Explicit template instantiation
template class Song<string, string>;
