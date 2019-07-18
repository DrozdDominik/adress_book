#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct Contact {
    int id;
    string name, surname, phoneNumber, email, adress;
};

vector<Contact> loadData(vector<Contact> contacts) {
    string line;
    int lineNumber = 1;
    fstream file;
    Contact singleContact;

    file.open("contacts.txt", ios::in);

    if(file.is_open()) {
        while(getline(file,line)) {
            string contact[6];
            int endOfString = line.length();
            int index = 0;
            int beginOfWord = 0;
            int lengthOfWord = 0;
            int conctactIndex = 0;

            for(index = 0; index < endOfString; index++) {

                if((int)line[index] == 124) {
                    lengthOfWord = index - beginOfWord;
                    contact[conctactIndex] = line.substr(beginOfWord, lengthOfWord);
                    beginOfWord = index + 1;
                    conctactIndex++;
                }
            }
            singleContact.id = atoi(contact[0].c_str());
            singleContact.name = contact[1];
            singleContact.surname = contact[2];
            singleContact.phoneNumber = contact[3];
            singleContact.email = contact[4];
            singleContact.adress = contact[5];

            contacts.push_back(singleContact);

        }
        file.close();

        return contacts;
    } else {
        file.close();
        return contacts;
    }
}

vector<Contact> addContact(vector<Contact> contacts) {
    fstream file;
    string name, surname, phoneNumber, adress, email;
    Contact singleContact;

    file.open("contacts.txt");
    if(file.good()) {
        file.close();
    } else {
        file.open("contacts.txt", ios::out);
        file.close();
    }

    int numberOfContacts = contacts.size();
    int lastId;
    if(contacts.empty()) {
        lastId = 0;
    } else {
        lastId = contacts[numberOfContacts - 1].id;
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

    singleContact = {lastId + 1, name, surname, phoneNumber, email, adress};

    contacts.push_back(singleContact);

    file.open("contacts.txt", ios::out | ios::app);
    if(file.good()) {
        file << contacts[numberOfContacts].id << "|";
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

bool isIdValid(vector<Contact> contacts, int idToDelete) {

    for(int i = 0; i < contacts.size(); i++) {
        if(contacts[i].id == idToDelete) {
            return true;
        }
    }
    return false;
}

vector<Contact> deleteContact(vector<Contact> contacts, int idToDelete) {

    char choice;
    fstream file;

    bool validId = isIdValid(contacts, idToDelete);
    if(validId) {

        cout << "Czy na pewno chcesz usunac ten kontakt? Aby potwierdzic wybierz <t>" << endl;
        cin >> choice;
        if(choice == 't') {

            file.open("temp.txt", ios::out);
            if(file.good()) {

                for(int i = 0; i < contacts.size(); i++) {
                    if(idToDelete == contacts[i].id) {
                        continue;
                    } else {
                        file << contacts[i].id << "|";
                        file << contacts[i].name << "|";
                        file << contacts[i].surname << "|";
                        file << contacts[i].phoneNumber << "|";
                        file << contacts[i].email << "|";
                        file << contacts[i].adress << "|" << endl;
                    }
                }

                file.close();

                remove("contacts.txt");
                rename("temp.txt", "contacts.txt");

                int indexToDelete = 0;
                for(int i = 0; i < contacts.size(); i++){
                    if(contacts[i].id == idToDelete){
                        indexToDelete = i;
                    }
                }
                contacts.erase(contacts.begin() + indexToDelete);

                cout << "Kontakt usuniety!" << endl;
                Sleep(1000);
                return contacts;
            } else {
                file.close();
                cout << "Blad odczytu pliku!" << endl;
                Sleep(1000);
                return contacts;
            }
        } else {
            cout << "Nie usunieto kontaktu!";
            Sleep(1000);
            return contacts;
        }
    } else {
        cout << "Kontakt o podanym id nie istnieje!";
        Sleep(1000);
        return contacts;
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

vector<Contact> editConctact(vector<Contact> contacts, int idToEdit, char choice, string dataToEdit) {
    fstream file;

    int indexToEdit;

    for(int i = 0; i < contacts.size(); i++) {
        if(contacts[i].id == idToEdit) {
            indexToEdit = i;
        }
    }

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

    file.open("contacts.txt", ios::out);
    if(file.good()) {
        if(idToEdit > 1) {
            for(int i = 0; i < indexToEdit; i++) {
                file << contacts[i].id << "|";
                file << contacts[i].name << "|";
                file << contacts[i].surname << "|";
                file << contacts[i].phoneNumber << "|";
                file << contacts[i].email << "|";
                file << contacts[i].adress << "|" << endl;
            }
        }

        file << contacts[indexToEdit].id << "|";
        file << contacts[indexToEdit].name << "|";
        file << contacts[indexToEdit].surname << "|";
        file << contacts[indexToEdit].phoneNumber << "|";
        file << contacts[indexToEdit].email << "|";
        file << contacts[indexToEdit].adress << "|" << endl;

        if(indexToEdit + 1 < contacts.size()) {
            for(int i = idToEdit; i < contacts.size(); i++) {
                file << contacts[i].id << "|";
                file << contacts[i].name << "|";
                file << contacts[i].surname << "|";
                file << contacts[i].phoneNumber << "|";
                file << contacts[i].email << "|";
                file << contacts[i].adress << "|" << endl;
            }
        }
        file.close();
        cout << "Kontakt zedytowany" << endl;
        Sleep(1500);
        return contacts;
    } else {
        file.close();
        cout << "Blad odczytu pliku!" << endl;
        Sleep(1000);
        return contacts;
    }
}

int main() {
    vector<Contact> contacts;
    int numberOfContacts = 0;
    int isMenuActive = true;
    int isEditMenuActive = true;
    char choice;
    int idToEdit;
    int idToDelete;

    contacts = loadData(contacts);

    while(1) {
        if(isMenuActive) {
            system("cls");
            cout << "1. Dodaj nowy kontakt" << endl;
            cout << "2. Wyszukiwanie po imieniu" << endl;
            cout << "3. Wyszukiwanie po nazwisku" << endl;
            cout << "4. Wyswietl wszystkie kontakty" << endl;
            cout << "5. Usun kontakt" << endl;
            cout << "6. Edytuj kontakt" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "Twoj wybor: ";
            cin >> choice;

            if(choice == '1') {
                contacts = addContact(contacts);
            } else if(choice == '2') {
                isMenuActive = searchByName(contacts);
            } else if(choice == '3') {
                isMenuActive = searchBySurname(contacts);
            } else if(choice == '4') {
                isMenuActive = showAllContacts(contacts);
            } else if(choice == '5') {
                system("cls");
                cout << "Podaj id kontaktu: ";
                cin >> idToDelete;
                contacts = deleteContact(contacts, idToDelete);
            } else if(choice == '6') {
                system("cls");
                cout << "Podaj id kontaktu: ";
                cin >> idToEdit;
                isMenuActive = isEdit(contacts, idToEdit);
                isEditMenuActive = true;
            } else if(choice == '9') {
                exit(0);
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

    return 0;
}
