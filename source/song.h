#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>
#include <memory>

using namespace std;

template <typename GenreType, typename ArtistType>
class Song {
protected: 
    string title;
    ArtistType artist;
    GenreType genre;
    float length;

public:
    Song(const string& title, const ArtistType& artist, const GenreType& genre, float length);
    virtual void songDetails() const;
    string getTitle() const;
    virtual void play() const;
    virtual void pause() const;
    virtual void stop() const;
    virtual ~Song();
    static bool loadSongsFromFile(const string& filename, vector<shared_ptr<Song<GenreType, ArtistType>>>& songs);
};

#endif
