#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;

class User {
    int id;
    string name, password;

public:
    User(int=0, string="brak", string="");
    void registration(vector <User> &users);
    void loadUsers(vector<User> &users);
    int LogIn (vector <User> &users);
    void editPassword(vector<User> &users, int idToEdit);

};
