#include <utility>

#include "CsvFileServiceTest.h"
#include "SupplierRepositoryTest.h"
#include "ConfigurationServiceTest.h"
#include "ClientRepositoryTest.h"
#include "ProductsRepositoryTest.h"

#define fileForCsvFileServiceTest "tests/csv-file-service-test.csv"
#define fileForSupplierRepositoryTest "tests/supplier-test.csv"
#define fileForConfigurationServiceTest "tests/configuration-test.csv"
#define fileForClientRepositoryTest "tests/clients-test.csv"
#define fileForProductsRepositoryTest "tests/products-test.csv"

using namespace std;

void deleteFiles();

void testCsvFileService(string filePath);

void testSupplierRepository(const string &filePath);

void testConfigurationService(const string &filePath);

void testClientRepository(const string &filePath);

void testProductsRepository(const string &filePath);

int main() {
    deleteFiles();

    testCsvFileService(fileForCsvFileServiceTest);

    testSupplierRepository(fileForSupplierRepositoryTest);

    testConfigurationService(fileForConfigurationServiceTest);

    testClientRepository(fileForClientRepositoryTest);

    testProductsRepository(fileForProductsRepositoryTest);

    return 0;
}

void deleteFiles() {
    remove(fileForCsvFileServiceTest);
    remove(fileForSupplierRepositoryTest);
    remove(fileForConfigurationServiceTest);
    remove(fileForClientRepositoryTest);
    remove(fileForProductsRepositoryTest);
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
    ClientRepositoryTest::shouldGetClientByIdOne(filePath);
}

void testProductsRepository(const string &filePath) {
    ProductsRepositoryTest::shouldWriteProductsToFile(filePath);
    ProductsRepositoryTest::shouldGetAllProductsForSpecificOrderFromFile(filePath);
}
