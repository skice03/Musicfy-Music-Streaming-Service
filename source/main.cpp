#include "user.h"
#include "song.h"
#include "interface.h"
#include <string.h>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    // List of users
    vector<User> userList;
    if (!User::loadUsersFromFile("users.txt", userList)) {
        cerr << "Exiting the application due to file error." << endl;
        return 0;
    }

    // List of available songs
    vector<shared_ptr<Song<string, string>>> availableSongs;
    if (!Song<string, string>::loadSongsFromFile("songs.txt", availableSongs)) {
        cerr << "Exiting the application due to file error." << endl;
        return 0;
    }

    string name, pass;
    bool loginSuccess = false;

    while (true) {
        system("clear");
        Interface::LoginWindow(name, pass);

        // Check if the username and password match any predefined user
        for (const User& user : userList) {
            if (user.login(name, pass)) {
                loginSuccess = true;
                break;
            }
        }

        // If login is successful, break out of the loop
        if (loginSuccess) {
            Interface::LoggedIn(name);
            break;
        }

        // Prompt the user to try again or quit
        cout << "\nLogin failed! Type 'quit' to exit the application or verify your credentials and press any key to try again: ";
        string input;
        getline(cin, input);
        if (input == "quit") {
            cout << "Exiting the app, bye!" << endl;
            return 0;
        }
    }

    while (true) {
        // Show the size of available songs
        cout << "\nHere's a list of available songs:\n\n";
        for (size_t i = 0; i < availableSongs.size(); ++i) {
            cout << i + 1 << ".\n";
            availableSongs[i]->songDetails();
            cout << endl;
        }
        cout << "You can play a song by typing its index or quit the app by typing 'quit': ";

        string input;
        getline(cin, input);

        if (input == "quit") {
            cout << "Thanks for using Musicfy, we hope to see you again!" << endl;
            break;
        }

        // Validate the input
        bool validInput = false;
        size_t songIndex = 0;
        while (!validInput) {
            try {
                songIndex = stoi(input) - 1;
                if (songIndex < availableSongs.size()) {
                    validInput = true;
                } else {
                    cout << "Invalid index. Please try again: ";
                    getline(cin, input);
                }
            } catch (invalid_argument&) {
                cout << "Invalid input. Please enter a song index or type 'quit' to exit: ";
                getline(cin, input);
                if (input == "quit") {
                    cout << "Thanks for using Musicfy, we hope to see you again!" << endl;
                    return 0;
                }
            }
        }

        bool isPlaying = false;
        while (true) {
            if (!isPlaying) {
                system("clear");
                availableSongs[songIndex]->play();
                isPlaying = true;
            }

            cout << "Type 'pause' to pause playback or 'exit' to go back to the main menu: ";
            getline(cin, input);

            if (input == "pause") {
                system("clear");
                availableSongs[songIndex]->pause();
                isPlaying = false;
                while (true) {
                    cout << "Type 'play' to resume playback or 'exit' to go back to the main menu: ";
                    getline(cin, input);
                    if (input == "play") {
                        system("clear");
                        availableSongs[songIndex]->play();
                        isPlaying = true;
                        break;
                    } else if (input == "exit") {
                        availableSongs[songIndex]->stop();
                        system("clear");
                        isPlaying = false;
                        break;
                    }
                }
                if (input == "exit") {
                    system("clear");
                    break; // Break out of the outer while loop to return to the main menu
                }
            } else if (input == "exit") {
                availableSongs[songIndex]->stop();
                system("clear");
                isPlaying = false;
                break;
            }
        }
    }

    return 0;
}