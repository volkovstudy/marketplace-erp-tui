#include <iostream>
#include <utility>

#include "CsvFileServiceTest.h"
#include "SupplierRepositoryTest.h"

using namespace std;

void testCsvFileService(string filePath);
void testSupplierRepository(string filePath);

int main() {
    string filePath = "test.csv";
    cout << "Writing properties to " << filePath << endl;
    testCsvFileService(filePath);

    testSupplierRepository("supplier-test.csv");

    return 0;
}

void testCsvFileService(string filePath) {
    CsvFileServiceTest::shouldWritePropertiesToFile(std::move(filePath));
}

void testSupplierRepository(string filePath) {
    SupplierRepositoryTest::shouldWriteSupplierToFile(std::move(filePath));
}
