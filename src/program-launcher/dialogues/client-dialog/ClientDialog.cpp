#include "ClientDialog.h"

#include <iostream>

#include "../../../utils/Utils.h"

#define tab "\t"

#define addNewClientProgramChar "a"
#define listAllClientsProgramChar "l"
#define quitProgramChar "q"

#define yesChar "y"
#define editChar "e"
#define cancelChar "c"

using namespace std;

void ClientDialog::openManagementDialog() {
    cout << "You opened clients management section.";
    printSectionVariants();

    do {
        bool isUserWantToLeft = getChoiceAndExecuteActionAndReturnQuitResult();

        if (isUserWantToLeft) return;

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
            break;
        } else if (program == listAllClientsProgramChar) {
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
