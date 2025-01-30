#include "user.h"
#include "song.h"
#include "playlist.h"
#include "interface.h"
#include <string.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    // user list din fisier
    vector<User> userList;
    if (!User::loadUsersFromFile("users.txt", userList))
    {
        cerr << "Exiting the app due to file error." << endl;
        return 0;
    }

    // song list din fisier
    vector<shared_ptr<Song<string, string>>> availableSongs;
    if (!Song<string, string>::loadSongsFromFile("songs.txt", availableSongs))
    {
        cerr << "Exiting the app due to file error." << endl;
        return 0;
    }

    // playlist
    vector<Playlist<string, string>> playlists;

    string name, pass;
    bool loginSuccess = false;

    while (true)
    {
        system("clear");
        Interface::LoginWindow(name, pass);

        // verificare daca exista acest user / pass
        for (const User &user : userList)
        {
            if (user.login(name, pass))
            {
                loginSuccess = true;
                break;
            }
        }

        if (loginSuccess)
        {
            Interface::LoggedIn(name);
            break;
        }

        cout << "\nLogin failed! Type 'quit' to exit the app or verify your credentials and press any key to try again: ";
        string input;
        getline(cin, input);
        if (input == "quit")
        {
            cout << "Exiting the app, bye!" << endl;
            return 0;
        }
    }

    // meniu principal
    Interface::MainMenu(playlists, availableSongs);

    return 0;
}