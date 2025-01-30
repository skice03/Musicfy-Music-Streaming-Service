#include "song.h"
#include <iostream>
#include <fstream>
#include <sstream>

// constructor
template <typename GenreType, typename ArtistType>
Song<GenreType, ArtistType>::Song(const string &title, const ArtistType &artist, const GenreType &genre, float length)
{
    this->title = title;
    this->artist = artist;
    this->genre = genre;
    this->length = length;
}

// songs details
template <typename GenreType, typename ArtistType>
void Song<GenreType, ArtistType>::songDetails() const
{
    cout << "Song title: " << title << "\nArtist: " << artist << "\nGenre: " << genre << "\nLength: " << length << " minutes\n";
}

template <typename GenreType, typename ArtistType>
string Song<GenreType, ArtistType>::getTitle() const
{
    return title;
}

template <typename GenreType, typename ArtistType>
string Song<GenreType, ArtistType>::getArtist() const
{
    return artist;
}

// play / pause / stop song
template <typename GenreType, typename ArtistType>
void Song<GenreType, ArtistType>::play() const
{
    cout << "Now playing: " << title << " by " << artist << endl;
}

template <typename GenreType, typename ArtistType>
void Song<GenreType, ArtistType>::pause() const
{
    cout << "Pausing song: " << title << " by " << artist << endl;
}

template <typename GenreType, typename ArtistType>
void Song<GenreType, ArtistType>::stop() const
{
}

template <typename GenreType, typename ArtistType>
Song<GenreType, ArtistType>::~Song() {}

// citire din fisier
template <typename GenreType, typename ArtistType>
bool Song<GenreType, ArtistType>::loadSongsFromFile(const string &filename, vector<shared_ptr<Song<GenreType, ArtistType>>> &songs)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return false;
    }

    string line;
    bool fileNotEmpty = false;
    while (getline(file, line))
    {
        fileNotEmpty = true;
        stringstream ss(line);
        string title, artist, genre;
        float length;

        // datele pt . songs (name,artist,genre,length) sunt separate prin virgula (,)
        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');
        ss >> length;

        songs.push_back(make_shared<Song<GenreType, ArtistType>>(title, artist, genre, length));
    }

    file.close();
    if (!fileNotEmpty)
    {
        cerr << "File is empty: " << filename << endl;
        return false;
    }

    return true;
}

// template
template class Song<string, string>;
