#include "OrdersDialog.h"
#include "../../../utils/Utils.h"

#include <iostream>

#define addNewOrderProgramChar "a"
#define listAllOrdersProgramChar "l"
#define quitProgramChar "q"

#define sectionName "orders management"

using namespace std;

void OrdersDialog::openManagementDialog() {
    cout << "You opened orders management section. ";
    printSectionVariants();

    do {
        bool isUserWantToLeft = getChoiceAndExecuteActionAndReturnQuitResult();

        if (isUserWantToLeft) return;

        cout << endl << endl << "You came back to the " << sectionName << " section." << endl;
        printSectionVariants();
    } while (true);
}

void OrdersDialog::printSectionVariants() {
    cout << "What do you want to do?" << endl << endl;

    cout << "(A)dd new order;" << endl;
    cout << "(L)ist all orders;" << endl;
    cout << "(Q)uit from the section;" << endl;
}

bool OrdersDialog::getChoiceAndExecuteActionAndReturnQuitResult() {
    do {
        cout << endl << "Your choice (A, L, Q): ";

        string program;
        cin >> program;
        Utils::toLowerCase(&program);

        if (program == addNewOrderProgramChar) {
            break;
        } else if (program == listAllOrdersProgramChar) {
            break;
        } else if (program == quitProgramChar) {
            cout << endl << "You left " << sectionName " section." << endl;
            return true;
        } else {
            cout << endl << "Wrong input. Try again." << endl;
        }
    } while (true);

    return false;
}
