#include "ClientAddingDialog.h"
#include "../../../../utils/Utils.h"
#include "../../../../models/client/Client.h"
#include "../../../../repositories/client-repository/ClientRepository.h"

#include <iostream>

#define pathToClientsFile "marketplace-erp/clients.csv"

#define tab "\t"

#define yesChar "y"
#define editChar "e"
#define cancelChar "c"

using namespace std;

void getInformationAboutClient(string& name, string& email);
void saveClient(Client client);

void ClientAddingDialog::addClient() {
    cout << "Now you're going to add new client." << endl;

    string name, email;
    getInformationAboutClient(name, email);

    do {
        Utils::printDelimiter();

        cout << "Well, check the information about new client:" << endl;
        cout << "Name" << tab << name << endl;
        cout << "Email" << tab << email << endl;

        cout << endl << "Is it right?" << endl;
        cout << "(Y)es, (E)dit, (C)ancel: ";

        string program;
        cin >> program;
        Utils::toLowerCase(&program);

        if (program == yesChar) {
            Client client(name, email);
            saveClient(client);

            cout << endl << "Client added." << endl;

            break;
        } else if (program == editChar) {
            Utils::printDelimiter();
            getInformationAboutClient(name, email);
        } else if (program == cancelChar) {
            cout << endl << "You left adding new client." << endl;
            return;
        } else {
            cout << endl << "Wrong input. Try again." << endl;
        }
    } while (true);
}

void getInformationAboutClient(string& name, string& email) {
    cout << "Write the name: ";
    do {
        getline(cin, name);
    } while (name.empty());

    cout << "Write the email: ";
    do {
        cin >> email;
    } while (email.empty());
}

void saveClient(Client client) {
    ClientRepository clientRepository(pathToClientsFile);

    clientRepository.save(&client);
}
