#include "TablePrinter.h"

#include <iostream>
#include <sstream>

#define indentLength 10

using namespace std;

void printHorizontalLine(int length);

void printHeader(int lineLength, const string& tableName);

void printTableName(const string& tableName, int lineLength);

void TablePrinter::printVector(const vector<Client*>& clients) {
    int maxLengthOfName = 0, maxLengthOfEmail = 0;
    for (Client* client: clients) {
        int nameLength = (int) client->getFullName().length();
        maxLengthOfName = max(maxLengthOfName, nameLength);

        int emailLength = (int) client->getEmail().length();
        maxLengthOfEmail = max(maxLengthOfEmail, emailLength);
    }

    // indentLength * 2 => because of left & right indent
    // + 3 => because of three '|' characters in header
    int lineLength = maxLengthOfName + maxLengthOfEmail + (indentLength * 2) + 3;
    printHeader(lineLength, "*Clients*");

    cout << "|";
    cout.width(maxLengthOfName + indentLength);
    cout << "NAME " << " |";

    cout.width(maxLengthOfEmail + indentLength - 2); // -2 => because of two spaces in next line
    cout << "EMAIL " << " |";
    cout << endl;

    printHorizontalLine(lineLength);

    for (Client* client: clients) {
        cout << "| ";
        cout.width(maxLengthOfName + indentLength - 1);
        cout << right;
        cout << client->getFullName();
        cout << " |";

        cout.width(maxLengthOfEmail + indentLength -
                   2); // -2 => because of one space in " |" in NAME column & one space in the end
        cout << right;
        cout << client->getEmail();
        cout << " |" << endl;
    }

    printHorizontalLine(lineLength);
}

string makeClientLine(Client& client) {
    stringstream clientLine;
    clientLine << client.getFullName() << " <" << client.getEmail() << ">";
    return clientLine.str();
}

string makeProductLine(const pair<string, int>& product) {
    stringstream productLine;
    productLine << product.first << " - " << product.second << " units";
    return productLine.str();
}

void TablePrinter::printVector(const vector<Order*>& orders) {
    map<Order*, string> idStrings;
    map<Order*, string> clientLines;
    map<Order*, vector<string>> productLines;

    int maxLengthOfId = 0, maxLengthOfClientLine = 0, maxLengthOfProductLine = 0;
    for (Order* order: orders) {
        string idString = to_string(order->getId());
        idStrings[order] = idString;
        int idLength = (int) idString.length();
        maxLengthOfId = max(maxLengthOfId, idLength);

        Client client = *(order->getClient());
        string clientLine = makeClientLine(client);
        clientLines[order] = clientLine;
        maxLengthOfClientLine = max(maxLengthOfClientLine, (int) clientLine.length());

        vector<string> productsLines;
        for (pair<string, int> product: order->getProducts()) {
            string productLine = makeProductLine(product);
            maxLengthOfProductLine = max(maxLengthOfProductLine, (int) productLine.length());

            productsLines.push_back(productLine);
        }
        productLines[order] = productsLines;
    }

    // indentLength * 2 => because of left & right indent
    // + 4 => because of four '|' characters in header
    // + 4 => because of spaces before '|' characters in header
    int lineLength = maxLengthOfId + maxLengthOfClientLine + maxLengthOfProductLine + (indentLength * 2) + 4 + 4;
    printHeader(lineLength, "*Orders*");

    cout << "|";
    cout.width(maxLengthOfId + indentLength);
    cout << "ID " << " |";

    cout.width(maxLengthOfClientLine + 1); // +1 => because of 1 space in " |"
    cout << "CLIENT " << " |";

    cout.width(maxLengthOfProductLine + indentLength);
    cout << "PRODUCTS " << " |";
    cout << endl;

    printHorizontalLine(lineLength);

    int widthForId = maxLengthOfId + indentLength;
    // +1 => because we need a space after previous '|' in ID column AND because we don't have indent there
    int widthForClient = maxLengthOfClientLine + 1;
    int widthForProducts = maxLengthOfProductLine + indentLength;

    for (Order* order: orders) {
        cout << "|";

        cout.width(widthForId);
        cout << right << idStrings[order] << " |";

        cout.width(widthForClient);
        cout << right << clientLines[order] << " |";

        vector<string> productsLines = productLines[order];
        cout.width(widthForProducts);
        cout << right << (productsLines.empty() ? "" : productsLines.at(0)) << " |" << endl;

        // Starts from 1 because we've already printed the first line
        for (int i = 1; i < productsLines.size(); ++i) {
            string productLine = productsLines.at(i);

            cout << "|";

            cout.width(widthForId + 2); // +2 => because of the need to move the '|' to the right
            cout << right << "|";

            cout.width(widthForClient + 2); // +2 => because of the need to move the '|' to the right
            cout << right << "|";

            cout.width(widthForProducts);
            cout << right;
            cout << productLine << " |" << endl;
        }

        printHorizontalLine(lineLength);
    }
}

void printHorizontalLine(int length) {
    for (int i = 0; i < length; ++i) {
        cout << "-";
    }
    cout << endl;
}

void printHeader(int lineLength, const string& tableName) {
    printHorizontalLine(lineLength);
    printTableName(tableName, lineLength);
    printHorizontalLine(lineLength);
}

void printTableName(const string& tableName, int lineLength) {
    int lengthOfIndent = lineLength / 2;

    cout << "|";
    cout.width(lengthOfIndent);
    cout << tableName;
    cout.width(lengthOfIndent - 1); // -1 => because begins printing after all width
    cout << "|";
    cout << endl;
}
