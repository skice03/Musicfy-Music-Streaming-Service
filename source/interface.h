#ifndef INTERFACE_H
#define INTERFACE_H

#include "user.h"
#include "song.h"
#include "playlist.h"
#include <string>
#include <vector>
#include <memory>

class Interface
{
public:
    string name;
    string pass;
    static void LoginWindow(string &name, string &pass);
    static void LoggedIn(string name);
    static void MainMenu(vector<Playlist<string, string>> &playlists, const vector<shared_ptr<Song<string, string>>> &availableSongs);
    static void ShowSongs(const vector<shared_ptr<Song<string, string>>> &availableSongs);
    static void ShowPlaylists(const vector<Playlist<string, string>> &playlists);
};

#endif