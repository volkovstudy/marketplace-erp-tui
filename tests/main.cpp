#include <utility>

#include "CsvFileServiceTest.h"
#include "ConfigurationServiceTest.h"
#include "ClientRepositoryTest.h"
#include "ProductsRepositoryTest.h"
#include "OrderRepositoryTest.h"

#define fileForCsvFileServiceTest "tests/csv-file-service-test.csv"
#define fileForConfigurationServiceTest "tests/configuration-test.csv"
#define fileForClientRepositoryTest "tests/clients-test.csv"
#define fileForProductsRepositoryTest "tests/products-test.csv"
#define fileForOrderRepositoryTest "tests/orders-test.csv"

using namespace std;

void deleteFiles();

void testCsvFileService(string filePath);

void testConfigurationService(const string& filePath);

void testClientRepository(const string& filePath);

void testProductsRepository(const string& filePath);

void testOrderRepository(const string& filePathForOrders, const string& filePathForClients,
                         const string& filePathForProducts);

int main() {
    deleteFiles();

    testCsvFileService(fileForCsvFileServiceTest);

    testConfigurationService(fileForConfigurationServiceTest);

    testClientRepository(fileForClientRepositoryTest);

    testProductsRepository(fileForProductsRepositoryTest);

    testOrderRepository(fileForOrderRepositoryTest, fileForClientRepositoryTest, fileForProductsRepositoryTest);

    return 0;
}

void deleteFiles() {
    remove(fileForCsvFileServiceTest);
    remove(fileForConfigurationServiceTest);
    remove(fileForClientRepositoryTest);
    remove(fileForProductsRepositoryTest);
    remove(fileForOrderRepositoryTest);
}

void testCsvFileService(string filePath) {
    CsvFileServiceTest::shouldWritePropertiesToFile(std::move(filePath));
}

void testConfigurationService(const string& filePath) {
    cout << "Testing ConfigurationService:" << endl;
    ConfigurationServiceTest::shouldReturnOne(filePath);
    ConfigurationServiceTest::shouldSaveNewCurrentId(filePath);
}

void testClientRepository(const string& filePath) {
    ClientRepositoryTest::shouldWriteClientToFile(filePath);
    ClientRepositoryTest::shouldGetAllClientsFromFile(filePath);
    ClientRepositoryTest::shouldGetClientByIdOne(filePath);
}

void testProductsRepository(const string& filePath) {
    ProductsRepositoryTest::shouldWriteProductsToFile(filePath);
    ProductsRepositoryTest::shouldGetAllProductsForSpecificOrderFromFile(filePath);
}

void testOrderRepository(const string& filePathForOrders, const string& filePathForClients,
                         const string& filePathForProducts) {
    OrderRepositoryTest::shouldWriteOrderToFile(filePathForOrders, filePathForClients, filePathForProducts);
    OrderRepositoryTest::shouldGetAllOrdersFromFile(filePathForOrders, filePathForClients, filePathForProducts);
}
