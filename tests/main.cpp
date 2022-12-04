#include <iostream>
#include <utility>

#include "CsvFileServiceTest.h"

using namespace std;

void testCsvFileService(string filePath);

int main() {
    string filePath = "test.csv";
    cout << "Writing properties to " << filePath << endl;
    testCsvFileService(filePath);

    return 0;
}

void testCsvFileService(string filePath) {
    CsvFileServiceTest::shouldWritePropertiesToFile(std::move(filePath));
}
