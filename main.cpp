#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include "user.h"

using namespace std;

struct Contact {
    int id, userId;
    string name, surname, phoneNumber, email, adress;
};

string conversionIntToString(int number) {
    ostringstream ss;
    ss << number;
    string str = ss.str();

    return str;
}

int idOfLastContact(string fileName) {
    fstream file;
    char ch = ' ';
    fileName += ".txt";
    file.open(fileName.c_str(), ios::in);
    if(file.is_open()) {
        file.seekg(0, ios::end);
        if (file.tellg() == 0) {
            return 0;
        } else {
            file.seekg(-3, ios::end);
            bool keepLooping = true;
            while(keepLooping) {
                file.get(ch);
                if((int)ch == 10) {
                    keepLooping = false;
                } else {
                    file.seekg(-3,ios_base::cur);
                }
            }
            char firstChar;
            file.get(firstChar);
            int number = (int) firstChar - 48;
            return number;
        }
    } else {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        Sleep(1000);
        exit(0);
    }
}

int idOfFirstLine(string fileName) {
    fstream file;
    fileName += ".txt";
    char firstChar;
    file.open(fileName.c_str(), ios::in);
    if(file.is_open()) {
        file.get(firstChar);
        int number = (int) firstChar - 48;
        return number;
    } else {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        Sleep(1000);
        exit(0);
    }
}

Contact loadSingleContact(string singleContactData) {
    Contact singleContact;
    string singleData = "";
    int numberOfSingleData = 1;

    for (int charPosition = 0; charPosition < singleContactData.length(); charPosition++) {
        if (singleContactData[charPosition] != '|') {
            singleData += singleContactData[charPosition];
        } else {
            switch(numberOfSingleData) {
            case 1:
                singleContact.id = atoi(singleData.c_str());
                break;
            case 2:
                singleContact.userId = atoi(singleData.c_str());
                break;
            case 3:
                singleContact.name = singleData;
                break;
            case 4:
                singleContact.surname = singleData;
                break;
            case 5:
                singleContact.phoneNumber = singleData;
                break;
            case 6:
                singleContact.email = singleData;
                break;
            case 7:
                singleContact.adress = singleData;
                break;
            }
            singleData = "";
            numberOfSingleData++;
        }
    }
    return singleContact;
}

vector<Contact> loadContactsFromFile(vector<Contact> contacts, int idLoggedUser) {
    Contact singleContact;
    string singleContactData = "";
    fstream file;

    file.open("contacts.txt", ios::in);

    if (file.good() == true) {

        while (getline(file, singleContactData)) {
            singleContact = loadSingleContact(singleContactData);

            if(singleContact.userId == idLoggedUser) {
                contacts.push_back(singleContact);
            }
        }
        file.close();
        return contacts;

    }
    return contacts;
}

void writeAllContactsToFile(vector<Contact> contacts, string fileName) {
    fstream file;
    string lineWithContactData = "";

    file.open(fileName.c_str(), ios::out);
    if (file.good()) {
        for (vector<Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr++) {
            lineWithContactData += conversionIntToString(itr->id) + '|';
            lineWithContactData += conversionIntToString(itr->userId) + '|';
            lineWithContactData += itr->name + '|';
            lineWithContactData += itr->surname + '|';
            lineWithContactData += itr->phoneNumber + '|';
            lineWithContactData += itr->email + '|';
            lineWithContactData += itr->adress + '|';

            file << lineWithContactData << endl;
            lineWithContactData = "";
        }
        file.close();
    } else {
        cout << "Blad odczytu pliku!" << endl;
    }
}

vector<Contact> addContact(vector<Contact> contacts, int idLoggedUser) {
    fstream file;
    string name, surname, phoneNumber, adress, email;
    Contact singleContact;
    int numberOfLines = 0;

    file.open("contacts.txt");
    if(file.good()) {
        file.close();
    } else {
        file.open("contacts.txt", ios::out);
        file.close();
    }
    string fileName = "contacts";
    int numberOfContacts = contacts.size();

    file.open("contacts.txt", ios::in);
    if(file.good()) {
        string line;

        while(getline(file, line)) {

            numberOfLines ++;
        }

        file.close();
    } else {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        Sleep(1000);
        exit(0);
    }

    int lastId = 0;
    if (contacts.size() == 1 && numberOfLines == 1) {
        lastId = idOfFirstLine(fileName);
    } else if(contacts.size() == 0 && numberOfLines == 1) {

        lastId = idOfFirstLine(fileName);

    } else {
        lastId = idOfLastContact(fileName);
    }

    system("cls");
    cout << "Podaj imie kontaktu: ";
    cin >> name;

    cout << "Podaj nazwisko kontaktu: ";
    cin >> surname;

    int i = 0;
    while(i < numberOfContacts) {

        if((contacts[i].name == name) && (contacts[i].surname == surname)) {
            cout << "Taki kontakt juz istnieje. Wpisz inne dane: " << endl;
            cout << "Podaj imie kontaktu: ";
            cin >> name;
            cout << "Podaj nazwisko kontaktu: ";
            cin >> surname;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj numer telefonu: ";
    cin.ignore();
    getline(cin, phoneNumber);
    cout << "Podaj email: ";
    cin >> email;
    cout << "Podaj adres: ";
    cin.ignore();
    getline(cin, adress);

    lastId++;

    int nextId = lastId;

    singleContact = {nextId, idLoggedUser, name, surname, phoneNumber, email, adress};

    contacts.push_back(singleContact);

    file.open("contacts.txt", ios::out | ios::app);
    if(file.good()) {
        file << contacts[numberOfContacts].id << "|";
        file << contacts[numberOfContacts].userId << "|";
        file << contacts[numberOfContacts].name << "|";
        file << contacts[numberOfContacts].surname << "|";
        file << contacts[numberOfContacts].phoneNumber << "|";
        file << contacts[numberOfContacts].email << "|";
        file << contacts[numberOfContacts].adress << "|" << endl;
        cout << "Kontakt dodany" << endl;
        file.close();
        Sleep(1000);
        return contacts;
    } else {
        cout << "Nie udalo sie otworzyc pliku" << endl;
        Sleep(1000);
        exit(0);
    }
}

bool showAllContacts(vector<Contact> contacts) {
    char choice = '0';

    if(contacts.empty()) {
        system("cls");
        cout << "Brak kontaktow";
        Sleep(1500);
        return true;
    } else {
        system("cls");

        for(int i = 0; i < contacts.size(); i++) {

            cout << "ID: " << contacts[i].id << endl;
            cout << contacts[i].name << " " << contacts[i].surname << endl;
            cout << "Numer telefonu: " << contacts[i].phoneNumber << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Adres: " << contacts[i].adress << endl;
            cout << endl;
        }
        Sleep(1500);
        while(choice !=1) {
            cout << "Aby powrocic do menu glownego wybierz 1 ";
            cin >> choice;
            if(choice == '1') {
                return true;
            }
        }

    }
}
bool searchByName(vector<Contact> contacts) {
    string name;
    char choice = '0';
    system("cls");
    cout << "Podaj imie: ";
    cin >> name;
    int numberOfContactsFound = 0;
    for(int i = 0; i < contacts.size(); i++) {

        if(contacts[i].name == name) {
            numberOfContactsFound++;
            cout << endl;
            cout << "ID: " << contacts[i].id << endl;
            cout << contacts[i].name << " " << contacts[i].surname << endl;
            cout << "Numer telefonu: " << contacts[i].phoneNumber << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Adres: " << contacts[i].adress << endl;
            cout << endl;
        }
    }
    if(numberOfContactsFound == 0) {
        cout << "Brak pasujacych kontantow" << endl;
    }
    Sleep(1500);
    while(choice !=1) {
        cout << "Aby powrocic do menu wyszukiwania wybierz 1 ";
        cin >> choice;
        if(choice == '1') {
            return true;
        }
    }
}

bool searchBySurname(vector<Contact> contacts) {
    string surname;
    char choice = '0';
    system("cls");
    cout << "Podaj nazwisko: ";
    cin >> surname;
    int numberOfContactsFound = 0;

    for(int i = 0; i < contacts.size(); i++) {
        if(contacts[i].surname == surname) {
            numberOfContactsFound++;
            cout << endl;
            cout << "ID: " << contacts[i].id << endl;
            cout << contacts[i].name << " " << contacts[i].surname << endl;
            cout << "Numer telefonu: " << contacts[i].phoneNumber << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Adres: " << contacts[i].adress << endl;
            cout << endl;
        }
    }
    if(numberOfContactsFound == 0) {
        cout << "Brak pasujacych kontantow" << endl;
    }
    Sleep(1500);
    while(choice !=1) {
        cout << "Aby powrocic do menu wyszukiwania wybierz 1 ";
        cin >> choice;
        if(choice == '1') {
            return true;
        }
    }
}

bool isEdit (vector<Contact> contacts, int idToEdit) {
    if(contacts.empty()) {
        system("cls");
        cout << "Brak kontaktow";
        Sleep(1500);
        return true;
    }
    for(int i = 0; i < contacts.size(); i++) {
        if(contacts[i].id == idToEdit) {
            return false;
        }
    }
    system("cls");
    cout << "Brak kontaktu o podanym id";
    Sleep(1500);
    return true;

}

vector<Contact> editVectorOfContacts (vector<Contact> contacts, int indexToEdit, char choice, string dataToEdit) {

    switch(choice) {
    case '1':
        contacts[indexToEdit].name = dataToEdit;
        break;
    case '2':
        contacts[indexToEdit].surname = dataToEdit;
        break;
    case '3':
        contacts[indexToEdit].phoneNumber = dataToEdit;
        break;
    case '4':
        contacts[indexToEdit].email = dataToEdit;
        break;
    case '5':
        contacts[indexToEdit].adress = dataToEdit;
        break;
    }
    return contacts;
}

vector<Contact> createTempVectorOfContacts (int id) {
    Contact singleContact;
    vector<Contact> tempContacts;
    string singleContactData = "";

    fstream file;
    file.open("contacts.txt", ios::in);

    if (file.good() == true) {
        while (getline(file, singleContactData)) {
            singleContact = loadSingleContact(singleContactData);

            if(singleContact.id != id) {
                tempContacts.push_back(singleContact);
            }
        }
        file.close();
        return tempContacts;

    }
}

vector<Contact> editConctact (vector<Contact> contacts, int idToEdit, char choice, string dataToEdit) {
    fstream tempFile;
    vector<Contact> tempContacts;
    int indexToEdit;

    for(int i = 0; i < contacts.size(); i++) {
        if(contacts[i].id == idToEdit) {
            indexToEdit = i;
        }
    }
    contacts = editVectorOfContacts(contacts, indexToEdit, choice, dataToEdit);

    tempFile.open("contacts_temp.txt", ios::out | ios::app);
    if(tempFile.good()) {

        tempContacts = createTempVectorOfContacts(idToEdit);

        if(idToEdit > 1) {
            for(int i = 0; i < tempContacts.size(); i++) {

                if(tempContacts[i].id < idToEdit) {
                    tempFile << tempContacts[i].id << "|";
                    tempFile << tempContacts[i].userId << "|";
                    tempFile << tempContacts[i].name << "|";
                    tempFile << tempContacts[i].surname << "|";
                    tempFile << tempContacts[i].phoneNumber << "|";
                    tempFile << tempContacts[i].email << "|";
                    tempFile << tempContacts[i].adress << "|" << endl;
                }
            }
        }
        tempFile << contacts[indexToEdit].id << "|";
        tempFile << contacts[indexToEdit].userId << "|";
        tempFile << contacts[indexToEdit].name << "|";
        tempFile << contacts[indexToEdit].surname << "|";
        tempFile << contacts[indexToEdit].phoneNumber << "|";
        tempFile << contacts[indexToEdit].email << "|";
        tempFile << contacts[indexToEdit].adress << "|" << endl;

        if(idToEdit < tempContacts.size() + 1) {
            for(int i = 0; i < tempContacts.size(); i++) {
                if(tempContacts[i].id > idToEdit) {
                    tempFile << tempContacts[i].id << "|";
                    tempFile << tempContacts[i].userId << "|";
                    tempFile << tempContacts[i].name << "|";
                    tempFile << tempContacts[i].surname << "|";
                    tempFile << tempContacts[i].phoneNumber << "|";
                    tempFile << tempContacts[i].email << "|";
                    tempFile << tempContacts[i].adress << "|" << endl;
                }
            }
        }
        tempFile.close();
        remove("contacts.txt");
        rename("contacts_temp.txt", "contacts.txt");
        cout << "Kontakt zedytowany" << endl;
        Sleep(1500);
        return contacts;
    } else {
        tempFile.close();
        cout << "Blad odczytu pliku!" << endl;
        Sleep(1000);
        return contacts;
    }
}

vector<Contact> deleteContact(vector<Contact> contacts) {
    fstream tempFile;
    vector<Contact> tempContacts;
    int idToDelete = 0;
    char choice;
    bool isContactExist = false;

    system("cls");
    if (!contacts.empty()) {
        cout << "Podaj id kontaktu do usuniecia: ";
        cin >> idToDelete;

        tempContacts = createTempVectorOfContacts(idToDelete);

        for (vector<Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr++) {
            if (itr->id == idToDelete) {
                isContactExist = true;
                cout << endl << "Czy na pewno chcesz usunac ten kontakt? Aby potwierdzic wybierz 't' ";
                cin >> choice;
                if (choice == 't') {

                    contacts.erase(itr);
                    tempFile.open("temp.txt", ios::out);
                    if(tempFile.good()) {
                        string fileName = "temp.txt";

                        writeAllContactsToFile(tempContacts, fileName);
                        tempFile.close();
                    } else {
                        tempFile.close();
                        cout << "Blad odczytu pliku!" << endl;
                        Sleep(1000);
                    }

                    remove("contacts.txt");
                    rename("temp.txt", "contacts.txt");

                    cout << "Kontakt usuniety!" << endl;
                    Sleep(1000);
                    return contacts;
                } else {
                    cout << "Nie usunieto kontaktu!";
                    Sleep(1000);
                    return contacts;
                }
            }
        }
        if (isContactExist == false) {
            cout << "Kontakt o podanym id nie istnieje!" << endl;
            Sleep(1000);
            return contacts;
        }
    } else {
        cout << "Brak kontaktow!" << endl;
        Sleep(1000);
        return contacts;
    }
}

int main() {
    vector <User> users;
    vector<Contact> contacts;
    int idLoggedUser = 0;
    int numberOfContacts = 0;
    bool isMenuActive = true;
    bool isEditMenuActive = false;
    char choice;
    int idToEdit;
    int idToDelete;

    User newUser;
    newUser.loadUsers(users);

    while(1) {
        if(idLoggedUser == 0) {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> choice;

            if(choice == '1') {
                User newUser;
                newUser.registration(users);
            } else if (choice == '2') {
                User newUser;
                idLoggedUser = newUser.LogIn(users);
            } else if (choice == '9') {
                exit(0);
            }
        } else {

            contacts = loadContactsFromFile(contacts, idLoggedUser);

            while(idLoggedUser != 0) {

                if(isMenuActive) {
                    system("cls");
                    cout << "1. Dodaj nowy kontakt" << endl;
                    cout << "2. Wyszukiwanie po imieniu" << endl;
                    cout << "3. Wyszukiwanie po nazwisku" << endl;
                    cout << "4. Wyswietl wszystkie kontakty" << endl;
                    cout << "5. Usun kontakt" << endl;
                    cout << "6. Edytuj kontakt" << endl;
                    cout << "7. Zmien haslo" << endl;
                    cout << "8. Wyloguj sie" << endl;
                    cout << "Twoj wybor: ";
                    cin >> choice;

                    if(choice == '1') {
                        contacts = addContact(contacts,idLoggedUser);
                    } else if(choice == '2') {
                        isMenuActive = searchByName(contacts);
                    } else if(choice == '3') {
                        isMenuActive = searchBySurname(contacts);
                    } else if(choice == '4') {
                        isMenuActive = showAllContacts(contacts);
                    } else if(choice == '5') {
                        contacts = deleteContact(contacts);
                    } else if(choice == '6') {
                        system("cls");
                        cout << "Podaj id kontaktu: ";
                        cin >> idToEdit;
                        isMenuActive = isEdit(contacts, idToEdit);
                        isEditMenuActive = true;
                    } else if(choice == '7') {
                        User newUser;
                        newUser.editPassword(users, idLoggedUser);
                    } else if (choice == '8') {
                        contacts.clear();
                        idLoggedUser = 0;
                    }

                } else {
                    while(isEditMenuActive) {
                        system("cls");
                        cout << "Edytuj:" << endl;
                        cout << "1. Imie" << endl;
                        cout << "2. Nazwisko" << endl;
                        cout << "3. Numer telefonu" << endl;
                        cout << "4. Email" << endl;
                        cout << "5. Adres" << endl;
                        cout << "6. Powrot do menu glownego" << endl;
                        cout << "Twoj wybor: ";
                        cin >> choice;
                        if(choice == '1') {
                            system("cls");
                            string editName;
                            cout << "Podaj nowe imie: ";
                            cin >> editName;
                            contacts = editConctact(contacts, idToEdit, choice, editName);
                        } else if (choice == '2') {
                            system("cls");
                            string editSurname;
                            cout << "Podaj nowe nazwisko: ";
                            cin >> editSurname;
                            contacts = editConctact(contacts, idToEdit,choice,editSurname);
                        } else if (choice == '3') {
                            system("cls");
                            string editPhoneNumber;
                            cout << "Podaj nowy numer telefonu: ";
                            cin.ignore();
                            getline(cin, editPhoneNumber);
                            contacts = editConctact(contacts, idToEdit,choice,editPhoneNumber);
                        } else if (choice == '4') {
                            system("cls");
                            string editEmail;
                            cout << "Podaj nowy email: ";
                            cin >> editEmail;
                            contacts = editConctact(contacts, idToEdit,choice,editEmail);
                        } else if (choice == '5') {
                            system("cls");
                            string editAdress;
                            cout << "Podaj nowy adres: ";
                            cin.ignore();
                            getline(cin, editAdress);
                            contacts = editConctact(contacts, idToEdit,choice,editAdress);
                        } else if (choice == '6') {
                            contacts = contacts;
                            isEditMenuActive = false;
                            isMenuActive = true;

                        }
                    }
                }
            }
        }
    }
    return 0;
}
