#include "interface.h"
#include <string.h>
#include <iostream>

using namespace std;

void Interface::LoginWindow(string& name, string& pass) {
    system("clear");
    cout<<"Welcome to Musicfy - A music streaming platform\n\nPlease enter your login credentials to continue:\n\n";
    cout<<"Username: "; getline(cin, name);
    cout<<"Password: "; getline(cin, pass);
}

void Interface::LoggedIn(string name) {
    cout<<"\nLogin successful, welcome back "<<name<<endl;
}