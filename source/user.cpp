#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>

// contructor
User::User(string name, string pass)
{
    this->username = name;
    this->password = pass;
}

// verificare date login
bool User::login(string name, string pass) const
{
    return this->username == name && this->password == pass;
}

// logout
void User::logout()
{
    cout << "User logged out!" << endl;
}

// citire users din fisier users.txt
bool User::loadUsersFromFile(const string &filename, vector<User> &users)
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
        string username, password;

        // datele pt . users (name/pass) sunt separate prin virgula (,)
        getline(ss, username, ',');
        getline(ss, password, ',');

        users.push_back(User(username, password));
    }

    file.close();
    if (!fileNotEmpty)
    {
        cerr << "File is empty: " << filename << endl;
        return false;
    }

    return true;
}
