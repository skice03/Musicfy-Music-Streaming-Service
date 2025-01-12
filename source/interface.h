#ifndef INTERFACE_H
#define INTERFACE_H

#include "user.h"
#include <string>

class Interface {
public:
    string name;
    string pass;
    static void LoginWindow(string& name, string& pass);
    static void LoggedIn(string name);
    static void Playlists(int& songs);
};

#endif