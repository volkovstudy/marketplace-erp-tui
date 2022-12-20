#include "TablePrinter.h"

#include <iostream>

#define indentLength 10

using namespace std;

void printHorizontalLine(int length);

void printHeader(int lineLength, const string& tableName);

void printTableName(const string& tableName, int lineLength);

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
