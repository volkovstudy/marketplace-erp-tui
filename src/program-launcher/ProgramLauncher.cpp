#include "ProgramLauncher.h"

#include <iostream>
#include <string>

#include "../utils/Utils.h"
#include "dialogues/client-dialog/ClientDialog.h"
#include "dialogues/orders-dialog/OrdersDialog.h"

#define clientsManagementProgram "c"
#define ordersManagementProgram "o"
#define quitProgram "q"

using namespace std;

void printProgramSections();
void getChoiceAndExecute();

[[noreturn]] void ProgramLauncher::start() {
    cout << "Hello! ";
    printProgramSections();

    while (true) {
        getChoiceAndExecute();

        cout << endl << endl << "You came back to the main section." << endl;
        printProgramSections();
    }
}

void printProgramSections() {
    cout << "What do you want to open?" << endl << endl;

    cout << "(C)lients management;" << endl;
    cout << "(O)rders management;" << endl;
    cout << "(Q)uit;" << endl;
}

void getChoiceAndExecute() {
    do {
        cout << endl << "Your choice (C, O, Q): ";

        string program;
        cin >> program;
        Utils::toLowerCase(&program);

        if (program == clientsManagementProgram) {
            cout << endl << endl;
            ClientDialog::openManagementDialog();
            break;
        } else if (program == ordersManagementProgram) {
            cout << endl << endl;
            OrdersDialog::openManagementDialog();
            break;
        } else if (program == quitProgram) {
            cout << endl << "Bye!" << endl;
            ::exit(0);
        } else {
            cout << endl << "Wrong input. Try again." << endl;
        }
    } while (true);
}
