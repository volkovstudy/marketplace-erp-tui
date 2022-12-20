#include "TablePrinter.h"

#include <iostream>

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
