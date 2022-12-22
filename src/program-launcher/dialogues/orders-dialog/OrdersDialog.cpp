#include "OrdersDialog.h"
#include "../../../utils/Utils.h"
#include "../../../models/client/Client.h"
#include "../../../models/order/Order.h"
#include "../../../repositories/client-repository/ClientRepository.h"
#include "../../../repositories/order-repository/OrderRepository.h"
#include "../../../table-printer/TablePrinter.h"

#include <iostream>
#include <sstream>

#define tab "\t"
#define pathToClientsFile "marketplace-erp/clients.csv"
#define pathToOrdersFile "marketplace-erp/orders.csv"
#define pathToProductsFile "marketplace-erp/products.csv"

#define addNewOrderProgramChar "a"
#define listAllOrdersProgramChar "l"
#define quitProgramChar "q"

#define yesChar "y"
#define noChar "n"
#define editChar "e"
#define cancelChar "c"

using namespace std;

void getInformationAboutOrder(Client& client, map<string, int>& products);
vector<Client*> getAllClients();
string makeClientLine(const Client& client);
void printAllClients();
void readAndSaveProduct(map<string, int>& products);
void printProducts(map<string, int>& products);
void saveOrder(Order& order);

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
    cout << "Now you're going to add new order." << endl << endl;

    Client& client = *new Client("", "");
    map<string, int> products{};


    try {
        getInformationAboutOrder(client, products);
    } catch (exception& exception) {
        cout << "There are no clients! Add new client!" << endl;
        return;
    }

    do {
        Utils::printDelimiter();

        cout << "Well, check the information about new order:" << endl << endl;
        cout << "Client:" << endl << makeClientLine(client) << endl << endl;
        cout << "Products:" << endl;
        printProducts(products);

        cout << endl << "Is it right?" << endl;
        cout << "(Y)es, (E)dit, (C)ancel: ";

        string program;
        cin >> program;
        Utils::toLowerCase(&program);

        if (program == yesChar) {
            Order order(&client, products);
            saveOrder(order);
            break;
        } else if (program == editChar) {
            Utils::printDelimiter();

            products = {};

            getInformationAboutOrder(client, products);
        } else if (program == cancelChar) {
            cout << endl << "You left adding new order." << endl;
            return;
        } else {
            cout << endl << "Wrong input. Try again." << endl;
        }
    } while (true);
}

void getInformationAboutOrder(Client& client, map<string, int>& products) {
    vector<Client*> clients = getAllClients();

    if (clients.empty()) {
        throw *new exception;
    }

    cout << "All clients:" << endl;
    printAllClients();
    int clientNo;
    do {
        cout << "Choose a client (" << 1 << "-" << clients.size() << "): ";

        string inputClientNo;
        cin >> inputClientNo;

        try {
            clientNo = stoi(inputClientNo);
        } catch (invalid_argument& invalidArgument) {
            clientNo = -1;
            cout << "Write a number!" << endl;
        } catch (out_of_range& outOfRange) {
            clientNo = -1;
            cout << "Write a smaller number!" << endl;
        }
        clientNo -= 1; // -1 => because in printing clients using index+1
    } while (clientNo < 0 || clientNo > clients.size());

    client = *clients.at(clientNo);

    cout << endl << "Write the products: " << endl;

    readAndSaveProduct(products);

    do {
        cout << endl << "Do you want to add one more? (Y/N): ";

        string program;
        cin >> program;
        Utils::toLowerCase(&program);

        if (program == yesChar) {
            cout << endl;
            readAndSaveProduct(products);
        } else if (program == noChar) {
            return;
        } else {
            cout << endl << "Wrong input. Try again." << endl;
        }
    } while (true);
}

vector<Client*> getAllClients() {
    ClientRepository clientRepository(pathToClientsFile);
    vector<Client*> clients = clientRepository.getAll();

    return clients;
}

string makeClientLine(const Client& client) {
    stringstream clientLine;
    clientLine << client.getFullName() << " <" << client.getEmail() << ">";

    return clientLine.str();
}

void printAllClients() {
    vector<Client*> clients = getAllClients();

    vector<string> clientLines;
    for (int i = 0; i < clients.size(); ++i) {
        Client* client = clients.at(i);

        string clientLine = makeClientLine(*client);

        stringstream fullClientLine;
        int clientNo = i + 1;
        fullClientLine << clientNo << ") " << clientLine;

        clientLines.push_back(fullClientLine.str());
    }

    for (const string& line: clientLines) {
        cout << line << endl;
    }
}

void readAndSaveProduct(map<string, int>& products) {
    string name;
    cout << "Name: ";
    do {
        getline(cin, name);
    } while (name.empty());

    int amount;
    do {
        cout << "Amount: ";

        string inputAmount;
        cin >> inputAmount;

        try {
            amount = stoi(inputAmount);
        } catch (invalid_argument& invalidArgument) {
            amount = -1;
            cout << "Write a number!" << endl;
        } catch (out_of_range& outOfRange) {
            amount = -1;
            cout << "Write a smaller number!" << endl;
        }
    } while (amount < 0);

    products[name] = amount;
}

void printProducts(map<string, int>& products) {
    for (pair<string, int> product: products) {
        int amount = product.second;

        cout << product.first << " - " << amount;

        if (amount == 1)
            cout << " unit";
        else
            cout << " units";

        cout << endl;
    }
}

void saveOrder(Order& order) {
    ClientRepository clientRepository(pathToClientsFile);
    ProductsRepository productsRepository(pathToProductsFile);
    OrderRepository orderRepository(pathToOrdersFile, &clientRepository, &productsRepository);

    orderRepository.save(&order);
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
