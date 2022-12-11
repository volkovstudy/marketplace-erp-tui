#include <utility>

#include "CsvFileServiceTest.h"
#include "SupplierRepositoryTest.h"

#define fileForCsvFileServiceTest "tests/csv-file-service-test.csv"
#define fileForSupplierRepositoryTest "tests/supplier-test.csv"

using namespace std;

void deleteFiles();

void testCsvFileService(string filePath);
void testSupplierRepository(string filePath);

int main() {
    deleteFiles();

    testCsvFileService(fileForCsvFileServiceTest);

    testSupplierRepository(fileForSupplierRepositoryTest);

    return 0;
}

void deleteFiles() {
    remove(fileForCsvFileServiceTest);
    remove(fileForSupplierRepositoryTest);
}

void testCsvFileService(string filePath) {
    CsvFileServiceTest::shouldWritePropertiesToFile(std::move(filePath));
}

void testSupplierRepository(string filePath) {
    SupplierRepositoryTest::shouldWriteSupplierToFile(std::move(filePath));
}
