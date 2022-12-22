#include "ClientDialog.h"

#include <iostream>

#include "../../../utils/Utils.h"
#include "../../../repositories/client-repository/ClientRepository.h"
#include "../../../table-printer/TablePrinter.h"
#include "client-adding-dialog/ClientAddingDialog.h"

#define pathToClientsFile "marketplace-erp/clients.csv"

#define addNewClientProgramChar "a"
#define listAllClientsProgramChar "l"
#define quitProgramChar "q"

#define yesChar "y"
#define editChar "e"
#define cancelChar "c"

using namespace std;

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

        cout << "You came back to the clients management section." << endl;
        printSectionVariants();
    } while (true);
}

void ClientDialog::printSectionVariants() {
    cout << "What do you want to do?" << endl << endl;

    cout << "(A)dd new client;" << endl;
    cout << "(L)ist all clients;" << endl;
    cout << "(Q)uit from the section;" << endl;
}

void ClientDialog::addNewClient() {
    ClientAddingDialog::addClient();
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

void ClientDialog::listAllClients() {
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
