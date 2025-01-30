#include "playlist.h"
#include <iostream>
#include <algorithm>

// constructor
template <typename GenreType, typename ArtistType>
Playlist<GenreType, ArtistType>::Playlist(const string &name)
{
    this->name = name;
}

// add song
template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::addSong(const shared_ptr<Song<GenreType, ArtistType>> &song)
{
    songs.push_back(song);
}

// remove song
template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::removeSong(const shared_ptr<Song<GenreType, ArtistType>> &song)
{
    auto it = find(songs.begin(), songs.end(), song);
    if (it != songs.end())
    {
        songs.erase(it);
    }
}

// display songs
template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::showSongs() const
{
    for (const auto &song : songs)
    {
        song->songDetails();
        cout << endl;
    }
}

template <typename GenreType, typename ArtistType>
string Playlist<GenreType, ArtistType>::getName() const
{
    return name;
}

template <typename GenreType, typename ArtistType>
const vector<shared_ptr<Song<GenreType, ArtistType>>> &Playlist<GenreType, ArtistType>::getSongs() const
{
    return songs;
}

// create playlist
template <typename GenreType, typename ArtistType>
void Playlist<GenreType, ArtistType>::createPlaylist(vector<Playlist<GenreType, ArtistType>> &playlists, const vector<shared_ptr<Song<GenreType, ArtistType>>> &availableSongs)
{
    string playlistName;
    while (true)
    {
        cout << "Enter a name for your new playlist: ";
        getline(cin, playlistName);
        cout<<endl;
        if (playlistName.empty())
        {
            cout << "Playlist name cannot be empty. Please try again.\n";
            continue;
        }

        bool duplicateExists = false;
        for (const auto &playlist : playlists)
        {
            if (playlist.getName() == playlistName)
            {
                duplicateExists = true;
                break;
            }
        }

        if (duplicateExists)
        {
            cout << "A playlist with the name '" << playlistName << "' already exists. Please choose a different name.\n";
        }
        else
        {
            break;
        }
    }

   system("clear");

    Playlist<GenreType, ArtistType> newPlaylist(playlistName);
    cout << "Here's a list of songs that you can add to the playlist:\n\n";
    for (size_t i = 0; i < availableSongs.size(); ++i)
    {
        cout << i + 1 << ". ";
        availableSongs[i]->songDetails();
        cout << endl;
    }

    // add songs to playlist until input is "done"
    while (true)
    {
        string input;
        cout << "You can add songs to the playlist by entering their indices (type 'done' when finished): ";
        getline(cin, input);

        if (input == "done")
        {
            break;
        }
        try
        {
            size_t songIndex = stoi(input) - 1;
            if (songIndex < availableSongs.size())
            {
                bool songExists = false;
                for (const auto &song : newPlaylist.getSongs())
                {
                    if (song->getTitle() == availableSongs[songIndex]->getTitle())
                    {
                        songExists = true;
                        break;
                    }
                }
                if (!songExists)
                {
                    newPlaylist.addSong(availableSongs[songIndex]);
                    cout << "Added: " << availableSongs[songIndex]->getTitle() << " by " << availableSongs[songIndex]->getArtist() << "\n\n";
                }
                else
                {
                    cout << "The song is already in the playlist. Please choose another song.\n\n";
                }
            }
            else
            {
                cout << "Invalid index. Please try again.\n\n";
            }
        }
        catch (invalid_argument &)
        {
            cout << "Invalid input. Please enter a song index or 'done' to finish.\n\n";
        }
    }
    playlists.push_back(newPlaylist);
    system("clear");
    cout << "Playlist '" << playlistName << "' created successfully.\n";
}

// operator overloading for adding a song to the playlist
template <typename GenreType, typename ArtistType>
Playlist<GenreType, ArtistType> Playlist<GenreType, ArtistType>::operator+(const shared_ptr<Song<GenreType, ArtistType>> &song)
{
    this->addSong(song);
    return *this;
}

// operator overloading for removing a song from the playlist
template <typename GenreType, typename ArtistType>
Playlist<GenreType, ArtistType> Playlist<GenreType, ArtistType>::operator-(const shared_ptr<Song<GenreType, ArtistType>> &song)
{
    if (songs.empty())
    {
        cout << "Playlist is empty. Cannot remove a song.\n";
    }
    else
    {
        auto it = find(songs.begin(), songs.end(), song);
        if (it != songs.end())
        {
            songs.erase(it);
            cout << "Removed: " << song->getTitle() << endl;
        }
        else
        {
            cout << "Song not found in the playlist.\n";
        }
    }
    return *this;
}

// template
template class Playlist<string, string>;