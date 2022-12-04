#include <utility>

#include "CsvFileServiceTest.h"
#include "SupplierRepositoryTest.h"

using namespace std;

void testCsvFileService(string filePath);
void testSupplierRepository(string filePath);

int main() {
    testCsvFileService("csv-file-service-test.csv");

    testSupplierRepository("supplier-test.csv");

    return 0;
}

void testCsvFileService(string filePath) {
    CsvFileServiceTest::shouldWritePropertiesToFile(std::move(filePath));
}

void testSupplierRepository(string filePath) {
    SupplierRepositoryTest::shouldWriteSupplierToFile(std::move(filePath));
}
