#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User {
private:
    string username;
    string password;

public:
    // Default constructor
    User() : username(""), password("") {}
    // Constructor
    User(string name, string pass);

    // Methods
    bool login(string name, string pass) const;
    void logout();
    static bool loadUsersFromFile(const string& filename, vector<User>& users);
};

#endif
