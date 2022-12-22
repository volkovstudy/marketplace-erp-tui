#include "OrdersDialog.h"
#include "../../../utils/Utils.h"
#include "../../../repositories/client-repository/ClientRepository.h"
#include "../../../repositories/order-repository/OrderRepository.h"
#include "../../../table-printer/TablePrinter.h"
#include "order-adding-dialog/OrderAddingDialog.h"

#include <iostream>

#define pathToClientsFile "marketplace-erp/clients.csv"
#define pathToOrdersFile "marketplace-erp/orders.csv"
#define pathToProductsFile "marketplace-erp/products.csv"

#define addNewOrderProgramChar "a"
#define listAllOrdersProgramChar "l"
#define quitProgramChar "q"

using namespace std;

void OrdersDialog::openManagementDialog() {
    cout << "You opened orders management section. ";
    printSectionVariants();

    do {
        bool isUserWantToLeft = getChoiceAndExecuteActionAndReturnQuitResult();

        if (isUserWantToLeft) {
            Utils::printDelimiter();
            return;
        }

        Utils::printDelimiter();

        cout << "You came back to the orders management section." << endl;
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
            Utils::printDelimiter();
            addNewOrder();
            break;
        } else if (program == listAllOrdersProgramChar) {
            Utils::printDelimiter();
            listAllOrders();
            break;
        } else if (program == quitProgramChar) {
            cout << endl << "You left orders management section." << endl;
            return true;
        } else {
            cout << endl << "Wrong input. Try again." << endl;
        }
    } while (true);

    return false;
}

void OrdersDialog::addNewOrder() {
    OrderAddingDialog::addOrder();
}

void OrdersDialog::listAllOrders() {
    ClientRepository clientRepository(pathToClientsFile);
    ProductsRepository productsRepository(pathToProductsFile);
    OrderRepository orderRepository(pathToOrdersFile, &clientRepository, &productsRepository);

    vector<Order*> orders = orderRepository.getAll();

    if (orders.empty()) {
        cout << "There are no orders!" << endl;
        return;
    }

    cout << "All orders:" << endl;
    TablePrinter::printVector(orders);

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
