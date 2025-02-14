#include "interface.h"
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

// interfata din app
void Interface::LoginWindow(string &name, string &pass)
{
    system("clear");
    cout << "Welcome to Musicfy - A music streaming platform\n\nPlease enter your login credentials to continue:\n\n";
    cout << "Username: ";
    getline(cin, name);
    cout << "Password: ";
    getline(cin, pass);
}

void Interface::LoggedIn(string name)
{
    cout << "\nLogin successful, welcome back " << name << endl;
}

void Interface::ShowSongs(const vector<shared_ptr<Song<string, string>>> &availableSongs)
{
    while (true)
    {
        system("clear");
        cout << "Here's a list of available songs:\n\n";
        for (size_t i = 0; i < availableSongs.size(); ++i)
        {
            cout << i + 1 << ". ";
            availableSongs[i]->songDetails();
            cout << endl;
        }
        cout << "You can play a song by typing its index or go back to the main menu by typing 'exit': ";

        string input;
        getline(cin, input);

        if (input == "exit")
        {
            break;
        }

        bool validInput = false;
        while (!validInput)
        {
            if (all_of(input.begin(), input.end(), ::isdigit))
            {
                try
                {
                    size_t songIndex = stoi(input) - 1;
                    if (songIndex < availableSongs.size())
                    {
                        validInput = true;

                        bool isPlaying = false;
                        while (true)
                        {
                            if (!isPlaying)
                            {
                                system("clear");
                                availableSongs[songIndex]->play();
                                isPlaying = true;
                            }

                            cout << "Type 'pause' to pause playback or 'exit' to go back to the main menu: ";
                            getline(cin, input);

                            if (input == "pause")
                            {
                                system("clear");
                                availableSongs[songIndex]->pause();
                                isPlaying = false;
                                while (true)
                                {
                                    cout << "Type 'play' to resume playback or 'exit' to go back to the main menu: ";
                                    getline(cin, input);
                                    if (input == "play")
                                    {
                                        system("clear");
                                        availableSongs[songIndex]->play();
                                        isPlaying = true;
                                        break;
                                    }
                                    else if (input == "exit")
                                    {
                                        availableSongs[songIndex]->stop();
                                        system("clear");
                                        isPlaying = false;
                                        break;
                                    }
                                }
                                if (input == "exit")
                                {
                                    system("clear");
                                    break;
                                }
                            }
                            else if (input == "exit")
                            {
                                availableSongs[songIndex]->stop();
                                system("clear");
                                isPlaying = false;
                                break;
                            }
                        }
                    }
                    else
                    {
                        cout << "Invalid index. Please try again: ";
                        getline(cin, input);
                        if (input == "exit")
                            break;
                    }
                }
                catch (invalid_argument &)
                {
                    cout << "Invalid input. Please enter a valid song index or type 'exit' to go back to the main menu: ";
                    getline(cin, input);
                    if (input == "exit")
                        break;
                }
            }
            else if (input == "exit")
            {
                break;
            }
            else
            {
                cout << "Invalid input. Please enter a valid song index or type 'exit' to go back to the main menu: ";
                getline(cin, input);
                if (input == "exit")
                    break;
            }
        }
        if (input == "exit")
            break;
    }
}

void Interface::ShowPlaylists(const vector<Playlist<string, string>> &playlists)
{
    system("clear");
    if (playlists.empty())
    {
        cout << "No playlists available. Create a new playlist from the main menu.\n\n";
    }
    else
    {
        cout << "Available playlists:\n\n";
        for (const auto &playlist : playlists)
        {
            cout << "Playlist: " << playlist.getName() << "\n\n";
            playlist.showSongs();
            cout << endl;
        }
    }
    cout << "Press enter to return to the main menu...";
    string input;
    getline(cin, input);
}

void Interface::MainMenu(vector<Playlist<string, string>> &playlists, const vector<shared_ptr<Song<string, string>>> &availableSongs)
{
    while (true)
    {
        system("clear");
        cout << "Select an option:\n\n";
        cout << "1. Show list of songs\n";
        cout << "2. Show available playlists\n";
        cout << "3. Create a new playlist\n";
        cout << "4. Modify an existing playlist\n\n";
        cout << "Type 'quit' to exit the app.\n\n";
        cout << "Enter your choice: ";

        string input;
        getline(cin, input);

        if (input == "quit")
        {
            cout << "Thanks for using Musicfy, we hope to see you again!" << endl;
            break;
        }

        bool validChoice = false;
        while (!validChoice)
        {
            if (input == "quit")
            {
                cout << "Thanks for using Musicfy, we hope to see you again!" << endl;
                return;
            }
            else if (all_of(input.begin(), input.end(), ::isdigit))
            {
                try
                {
                    int choice = stoi(input);
                    if (choice == 1)
                    {
                        validChoice = true;
                        ShowSongs(availableSongs);
                    }
                    else if (choice == 2)
                    {
                        validChoice = true;
                        ShowPlaylists(playlists);
                    }
                    else if (choice == 3)
                    {
                        validChoice = true;
                        system("clear");
                        Playlist<string, string>::createPlaylist(playlists, availableSongs);
                        cout << "Press any key to return to the main menu...";
                        getline(cin, input);
                    }
                    else if (choice == 4)
                    {
                        validChoice = true;
                        system("clear");
                        if (playlists.empty())
                        {
                            cout << "No playlists available. Create a new playlist first.\n";
                            cout << "Press any key to return to the main menu...";
                            string input;
                            getline(cin, input); // Wait for user input before returning
                        }
                        else
                        {
                            // Display the list of playlists once
                            cout << "Select a playlist to modify:\n\n";
                            for (size_t i = 0; i < playlists.size(); ++i)
                            {
                                cout << i + 1 << ": " << playlists[i].getName() << "\n\n";
                            }

                            // Loop until the user enters a valid index or chooses to exit
                            while (true)
                            {
                                cout << "Enter the index of the playlist (or 'exit' to go back): ";
                                getline(cin, input);

                                if (input == "exit")
                                {
                                    break; // Exit the loop and return to the main menu
                                }

                                try
                                {
                                    size_t playlistIndex = stoi(input) - 1;
                                    if (playlistIndex < playlists.size())
                                    {
                                        // Valid index entered, proceed to modify the playlist
                                        system("clear");
                                        cout << "Modify Playlist: " << playlists[playlistIndex].getName() << "\n\n";
                                        cout << "1. Add a song\n";
                                        cout << "2. Remove a song\n";
                                        cout << "3. Show songs in playlist\n";
                                        cout << "4. Go back to the main menu\n\n";
                                        cout << "Enter your choice: ";

                                        while (true)
                                        {
                                            getline(cin, input);

                                            if (input == "1")
                                            {
                                                // Add a song
                                                system("clear");
                                                for (size_t i = 0; i < availableSongs.size(); ++i)
                                                {
                                                    cout << i + 1 << ". ";
                                                    availableSongs[i]->songDetails();
                                                    cout << endl;
                                                }
                                                cout << "You can add songs to the playlist by entering their indices (type 'done' when finished): \n";
                                                while (true)
                                                {
                                                    cout << "\nEnter the index of the song to add (or 'done' to finish): ";
                                                    getline(cin, input);
                                                    if (input == "done")
                                                        break;
                                                    try
                                                    {
                                                        size_t songIndex = stoi(input) - 1;
                                                        if (songIndex < availableSongs.size())
                                                        {
                                                            bool songExists = false;
                                                            for (const auto &song : playlists[playlistIndex].getSongs())
                                                            {
                                                                if (song->getTitle() == availableSongs[songIndex]->getTitle())
                                                                {
                                                                    songExists = true;
                                                                    break;
                                                                }
                                                            }
                                                            if (!songExists)
                                                            {
                                                                playlists[playlistIndex] = playlists[playlistIndex] + availableSongs[songIndex];
                                                                cout << "Added: " << availableSongs[songIndex]->getTitle() << endl;
                                                            }
                                                            else
                                                            {
                                                                cout << "The song is already in the playlist. Please choose another song.\n";
                                                            }
                                                        }
                                                        else
                                                        {
                                                            cout << "Invalid index. Please try again.\n";
                                                        }
                                                    }
                                                    catch (invalid_argument &)
                                                    {
                                                        cout << "Invalid input. Please enter a song index or 'done' to finish:\n";
                                                    }
                                                }
                                                break;
                                            }
                                            else if (input == "2")
                                            {
                                                // Remove a song
                                                if (playlists[playlistIndex].getSongs().empty())
                                                {
                                                    cout << "Playlist is empty. Cannot remove a song.\n"<<"\nEnter your choice: ";
                                                }
                                                else
                                                {
                                                    // Display the list of songs once
                                                    system("clear");
                                                    cout << "Remove songs from your playlist by entering their indices (type 'done' when finished): \n\n";
                                                    for (size_t i = 0; i < playlists[playlistIndex].getSongs().size(); ++i)
                                                    {
                                                        cout << i + 1 << ". ";
                                                        playlists[playlistIndex].getSongs()[i]->songDetails();
                                                        cout << endl;
                                                    }

                                                    // Loop until the user enters a valid index or types 'done'
                                                    bool doneRemoving = false;
                                                    while (!doneRemoving)
                                                    {
                                                        cout << "Enter the index of the song to remove (or 'done' to finish): ";
                                                        getline(cin, input);

                                                        if (input == "done")
                                                        {
                                                            doneRemoving = true; // Exit the removal loop
                                                            break;
                                                        }

                                                        try
                                                        {
                                                            size_t songIndex = stoi(input) - 1;
                                                            if (songIndex < playlists[playlistIndex].getSongs().size())
                                                            {
                                                                // Valid index, remove the song
                                                                auto songToRemove = playlists[playlistIndex].getSongs()[songIndex];
                                                                playlists[playlistIndex] = playlists[playlistIndex] - songToRemove;

                                                                // Display the updated playlist
                                                                cout << "Updated playlist:\n\n";
                                                                for (size_t i = 0; i < playlists[playlistIndex].getSongs().size(); ++i)
                                                                {
                                                                    cout << i + 1 << ". ";
                                                                    playlists[playlistIndex].getSongs()[i]->songDetails();
                                                                    cout << "\n";
                                                                }
                                                            }
                                                            else
                                                            {
                                                                // Invalid index, display the error message
                                                                cout << "Invalid index. Please try again.\n\n";
                                                            }
                                                        }
                                                        catch (invalid_argument &)
                                                        {
                                                            // Invalid input (not a number), display the error message
                                                            cout << "Invalid input. Please enter a song index or 'done' to finish.\n\n";
                                                        }
                                                    }

                                                    if (doneRemoving)
                                                    {
                                                        break; // Exit the outer loop and return to the previous menu
                                                    }
                                                }
                                            }
                                            else if (input == "3")
                                            {
                                                // Show songs in playlist
                                                system("clear");
                                                cout << "Songs in playlist '" << playlists[playlistIndex].getName() << "':\n\n";
                                                playlists[playlistIndex].showSongs();
                                                cout << "Press enter to go back...";
                                                getline(cin, input);
                                                break;
                                            }
                                            else if (input == "4")
                                            {
                                                // Go back to the main menu
                                                break;
                                            }
                                            else
                                            {
                                                // Invalid choice, display the error message without re-displaying the menu
                                                cout << "Invalid choice. Please try again.\n\n";
                                                cout << "Enter your choice: ";
                                            }
                                        }
                                        break; // Exit the playlist selection loop after modifying the playlist
                                    }
                                    else
                                    {
                                        // Invalid index, prompt the user to try again
                                        cout << "Invalid index. Please enter a valid index or 'exit' to go back.\n\n";
                                    }
                                }
                                catch (invalid_argument &)
                                {
                                    // Invalid input (not a number), prompt the user to try again
                                    cout << "Invalid input. Please enter a valid index or 'exit' to go back.\n\n";
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "Invalid choice. Please enter 1, 2, 3, 4, or 'quit': ";
                        getline(cin, input);
                    }
                }
                catch (invalid_argument &)
                {
                    cout << "Invalid choice. Please enter 1, 2, 3, 4, or 'quit': ";
                    getline(cin, input);
                }
            }
            else
            {
                cout << "Invalid choice. Please enter 1, 2, 3, 4, or 'quit': ";
                getline(cin, input);
            }
        }
    }
}