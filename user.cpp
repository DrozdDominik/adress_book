#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include "user.h"

using namespace std;

User::User(int i, string n, string p){

id = i;
name = n;
password = p;

}


void User::registration(vector <User> &users){
    User singleUser;
    fstream file;

    file.open("users.txt");
    if(file.good()) {
        file.close();
    } else {
        file.open("users.txt", ios::out);
        file.close();
    }

    cout << "Podaj nazwe uzytkownika: ";
    cin >> name;

    int i = 0;
    while(i < users.size()) {
        if(users[i].name == name) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> name;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> password;

    int numberOfUsers = users.size();
    int lastId;
    if(users.empty()) {
        lastId = 0;
    } else {
        lastId = users[numberOfUsers - 1].id;
    }

    singleUser = {lastId + 1, name, password};

    users.push_back(singleUser);

    file.open("users.txt", ios::out | ios::app);
    if(file.good()) {
        file << users[numberOfUsers].id << "|";
        file << users[numberOfUsers].name << "|";
        file << users[numberOfUsers].password << "|" << endl;
        cout << "Konto zalozone" << endl;
        file.close();

        Sleep(1000);
   }      else {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        Sleep(1000);

    }
}

void User::loadUsers(vector<User> &users){
    string line;
    int lineNumber = 1;
    fstream file;
    User singleUser;

    file.open("users.txt", ios::in);

    if(file.is_open()) {
        while(getline(file,line)) {
            string user[3];
            int endOfString = line.length();
            int index = 0;
            int beginOfWord = 0;
            int lengthOfWord = 0;
            int userIndex = 0;

            for(index = 0; index < endOfString; index++) {

                if((int)line[index] == 124) {
                    lengthOfWord = index - beginOfWord;
                    user[userIndex] = line.substr(beginOfWord, lengthOfWord);
                    beginOfWord = index + 1;
                    userIndex++;
                }
            }
            singleUser.id = atoi(user[0].c_str());
            singleUser.name = user[1];
            singleUser.password = user[2];

            users.push_back(singleUser);

        }
        file.close();


    } else {
        file.close();

    }

}


int User::LogIn (vector <User> &users){
    cout << "Podaj login: ";
    cin >> name;

    int i = 0;
    while(i < users.size()) {
        if(users[i].name == name) {
            for(int attempts = 0; attempts < 3; attempts++) {
                cout << "Podaj haslo. Pozostalo prob " << 3-attempts << ": ";
                cin >> password;
                if(users[i].password == password) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return users[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Program konczy dzialanie!" << endl;
            Sleep(3000);
            exit(0);
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}


void User::editPassword(vector<User> &users, int idToEdit){
    fstream file;

    int indexToEdit;
    string newPassword;
    cout << "Podaj nowe haslo: ";
    cin >> newPassword;
    for(int i = 0; i < users.size(); i++) {
        if(users[i].id == idToEdit) {
            indexToEdit = i;
        }
    }
    users[indexToEdit].password = newPassword;

    file.open("users.txt", ios::out);
    if(file.good()) {
        if(idToEdit > 1) {
            for(int i = 0; i < indexToEdit; i++) {
                file << users[i].id << "|";
                file << users[i].name << "|";
                file << users[i].password << "|" << endl;
            }
        }
        file << users[indexToEdit].id << "|";
        file << users[indexToEdit].name << "|";
        file << users[indexToEdit].password << "|" << endl;

        if(indexToEdit + 1 < users.size()) {
            for(int i = idToEdit; i < users.size(); i++) {
                file << users[i].id << "|";
                file << users[i].name << "|";
                file << users[i].password << "|" << endl;
            }
        }
        file.close();
        cout << "Haslo zostalo zmienione" << endl;
        Sleep(1500);

    } else {
        file.close();
        cout << "Blad odczytu pliku!" << endl;
        Sleep(1000);

    }
}
