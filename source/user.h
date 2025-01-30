#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User
{
private:
    string username;
    string password;

public:
    // contructor de baza
    User() : username(""), password("") {}
    User(string name, string pass);
    
    bool login(string name, string pass) const;
    void logout();
    static bool loadUsersFromFile(const string &filename, vector<User> &users);
};

#endif
