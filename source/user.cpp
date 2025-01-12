#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor definition
User::User(string name, string pass) {
    this->username = name;
    this->password = pass;
}

// Method to check login credentials
bool User::login(string name, string pass) const {
    return this->username == name && this->password == pass;
}

// Method to logout
void User::logout() {
    cout << "User logged out!" << endl;
}

// Method to load users from file
bool User::loadUsersFromFile(const string& filename, vector<User>& users) {
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
        string username, password;

        // Read user details separated by commas
        getline(ss, username, ',');
        getline(ss, password, ',');

        users.push_back(User(username, password));
    }

    file.close();
    if (!fileNotEmpty) {
        cerr << "File is empty: " << filename << endl;
        return false;
    }

    return true;
}
