#include "OrderAddingDialog.h"
#include "../../../../models/client/Client.h"
#include "../../../../utils/Utils.h"
#include "../../../../models/order/Order.h"
#include "../../../../repositories/client-repository/ClientRepository.h"
#include "../../../../repositories/products-repository/ProductsRepository.h"
#include "../../../../repositories/order-repository/OrderRepository.h"

#include <iostream>
#include <vector>
#include <sstream>

#define pathToClientsFile "marketplace-erp/clients.csv"
#define pathToOrdersFile "marketplace-erp/orders.csv"
#define pathToProductsFile "marketplace-erp/products.csv"

#define yesChar "y"
#define noChar "n"
#define editChar "e"
#define cancelChar "c"

using namespace std;

vector<Client*> getAllClients();
string makeClientLine(const Client& client);
void getInformationAboutOrder(Client& client, vector<Product*> products);
void printAllClients();
void readAndSaveProduct(vector<Product*> products);
void printProducts(vector<Product*> products);
void saveOrder(Order& order);

void OrderAddingDialog::addOrder() {
    cout << "Now you're going to add new order." << endl << endl;

    Client& client = *new Client(-1, "", "");
    vector<Product*> products{};

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

            cout << endl << "Order saved." << endl;

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

void getInformationAboutOrder(Client& client, vector<Product*> products) {
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

void readAndSaveProduct(vector<Product*> products) {
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

    Product* product = new Product(name, amount);
    products.push_back(product);
}

void printProducts(vector<Product*> products) {
    for (Product* product: products) {
        int amount = product->getAmount();

        cout << product->getName() << " - " << amount;

        if (amount == 1)
            cout << " unit";
        else
            cout << " units";

        cout << endl;
    }
}

void saveOrder(Order& order) {
    OrderRepository orderRepository(pathToOrdersFile, new ClientRepository(pathToClientsFile), new ProductsRepository(pathToProductsFile));

    orderRepository.save(&order);
}

vector<Client*> getAllClients() {
    ClientRepository clientRepository(pathToClientsFile);

    return clientRepository.getAll();
}

string makeClientLine(const Client& client) {
    stringstream clientLine;
    clientLine << client.getFullName() << " <" << client.getEmail() << ">";

    return clientLine.str();
}
