#include <utility>

#include "CsvFileServiceTest.h"
#include "SupplierRepositoryTest.h"
#include "ConfigurationServiceTest.h"
#include "ClientRepositoryTest.h"

#define fileForCsvFileServiceTest "tests/csv-file-service-test.csv"
#define fileForSupplierRepositoryTest "tests/supplier-test.csv"
#define fileForConfigurationServiceTest "tests/configuration-test.csv"
#define fileForClientRepositoryTest "tests/clients-test.csv"

using namespace std;

void deleteFiles();

void testCsvFileService(string filePath);

void testSupplierRepository(const string &filePath);

void testConfigurationService(const string &filePath);

void testClientRepository(const string &filePath);

int main() {
    deleteFiles();

    testCsvFileService(fileForCsvFileServiceTest);

    testSupplierRepository(fileForSupplierRepositoryTest);

    testConfigurationService(fileForConfigurationServiceTest);

    testClientRepository(fileForClientRepositoryTest);

    return 0;
}

void deleteFiles() {
    remove(fileForCsvFileServiceTest);
    remove(fileForSupplierRepositoryTest);
    remove(fileForConfigurationServiceTest);
    remove(fileForClientRepositoryTest);
}

void testCsvFileService(string filePath) {
    CsvFileServiceTest::shouldWritePropertiesToFile(std::move(filePath));
}

void testSupplierRepository(const string &filePath) {
    SupplierRepositoryTest::shouldWriteSupplierToFile(filePath);
    SupplierRepositoryTest::shouldGetAllSuppliersFromFile(filePath);
}

void testConfigurationService(const string &filePath) {
    cout << "Testing ConfigurationService:" << endl;
    ConfigurationServiceTest::shouldReturnOne(filePath);
    ConfigurationServiceTest::shouldSaveNewCurrentId(filePath);
}

void testClientRepository(const string &filePath) {
    ClientRepositoryTest::shouldWriteClientToFile(filePath);
    ClientRepositoryTest::shouldGetAllClientsFromFile(filePath);
}
