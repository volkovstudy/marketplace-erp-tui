#include "ClientDialog.h"

#include <iostream>

#include "../../../utils/Utils.h"
#include "../../../repositories/client-repository/ClientRepository.h"
#include "../../../table-printer/TablePrinter.h"

#define tab "\t"
#define pathToClientsFile "marketplace-erp/clients.csv"

#define addNewClientProgramChar "a"
#define listAllClientsProgramChar "l"
#define quitProgramChar "q"

#define yesChar "y"
#define editChar "e"
#define cancelChar "c"

using namespace std;

void getInformationAboutClient(string& name, string& email);
void saveClient(Client client);

void ClientDialog::openManagementDialog() {
    cout << "You opened clients management section. ";
    printSectionVariants();

    do {
        bool isUserWantToLeft = getChoiceAndExecuteActionAndReturnQuitResult();

        if (isUserWantToLeft) {
            Utils::printDelimiter();
            return;
        }

        Utils::printDelimiter();

        cout << endl << endl << "You came back to the clients management section." << endl;
        printSectionVariants();
    } while (true);
}

void ClientDialog::printSectionVariants() {
    cout << "What do you want to do?" << endl << endl;

    cout << "(A)dd new client;" << endl;
    cout << "(L)ist all clients;" << endl;
    cout << "(Q)uit from the section;" << endl;
}

bool ClientDialog::getChoiceAndExecuteActionAndReturnQuitResult() {
    do {
        cout << endl << "Your choice (A, L, Q): ";

        string program;
        cin >> program;
        Utils::toLowerCase(&program);

        if (program == addNewClientProgramChar) {
            Utils::printDelimiter();
            addNewClient();
            break;
        } else if (program == listAllClientsProgramChar) {
            Utils::printDelimiter();
            listAllClients();
            break;
        } else if (program == quitProgramChar) {
            cout << endl << "You left clients management section." << endl;
            return true;
        } else {
            cout << endl << "Wrong input. Try again." << endl;
        }
    } while (true);

    return false;
}

void ClientDialog::addNewClient() {
    cout << "Now you're going to add new client." << endl;

    string name, email;
    getInformationAboutClient(name, email);

    do {
        Utils::printDelimiter();

        cout << endl << "Well, check the information about new client:" << endl;
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

void ClientDialog::listAllClients() {
    cout << endl;

    ClientRepository clientRepository(pathToClientsFile);
    vector<Client*> clients = clientRepository.getAll();

    if (clients.empty()) {
        cout << "There are no clients!" << endl;
        return;
    }

    cout << "All clients:" << endl;
    TablePrinter::printVector(clients);

    cout << endl << "What do you want to do?" << endl;
    cout << "(Q)uit;" << endl;

    do {
        cout << endl << "Your choice (Q): ";

        string program;
        cin >> program;
        Utils::toLowerCase(&program);

        if (program == quitProgramChar) {
            return;
        } else {
            cout << endl << "Wrong input. Try again." << endl;
        }
    } while (true);
}
