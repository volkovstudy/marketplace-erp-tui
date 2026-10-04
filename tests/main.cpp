#include <string>
#include <utility>

#include "ClientRepositoryTest.h"
#include "ConfigurationServiceTest.h"
#include "CsvFileServiceTest.h"
#include "OrderRepositoryTest.h"
#include "ProductsRepositoryTest.h"
#include "TablePrinterTest.h"

#define fileForCsvFileServiceTest "tests/csv-file-service-test.csv"
#define fileForConfigurationServiceTest "tests/configuration-test.csv"
#define fileForClientRepositoryTest "tests/clients-test.csv"
#define fileForProductsRepositoryTest "tests/products-test.csv"
#define fileForOrderRepositoryTest "tests/orders-test.csv"

void deleteFiles();

void testCsvFileService(std::string filePath);

void testConfigurationService(const std::string& filePath);

void testClientRepository(const std::string& filePath);

void testProductsRepository(const std::string& filePath);

void testOrderRepository(const std::string& filePathForOrders,
                         const std::string& filePathForClients,
                         const std::string& filePathForProducts);

void testTablePrinter();

int main() {
  deleteFiles();

  testCsvFileService(fileForCsvFileServiceTest);

  testConfigurationService(fileForConfigurationServiceTest);

  testClientRepository(fileForClientRepositoryTest);

  testProductsRepository(fileForProductsRepositoryTest);

  testOrderRepository(fileForOrderRepositoryTest, fileForClientRepositoryTest,
                      fileForProductsRepositoryTest);

  testTablePrinter();

  return 0;
}

void deleteFiles() {
  remove(fileForCsvFileServiceTest);
  remove(fileForConfigurationServiceTest);
  remove(fileForClientRepositoryTest);
  remove(fileForProductsRepositoryTest);
  remove(fileForOrderRepositoryTest);
}

void testCsvFileService(std::string filePath) {
  CsvFileServiceTest::shouldWritePropertiesToFile(std::move(filePath));
}

void testConfigurationService(const std::string& filePath) {
  std::cout << "Testing ConfigurationService:" << std::endl;
  ConfigurationServiceTest::shouldReturnOne(filePath);
  ConfigurationServiceTest::shouldSaveNewCurrentId(filePath);
}

void testClientRepository(const std::string& filePath) {
  ClientRepositoryTest::shouldWriteClientToFile(filePath);
  ClientRepositoryTest::shouldGetAllClientsFromFile(filePath);
  ClientRepositoryTest::shouldGetClientByIdOne(filePath);
}

void testProductsRepository(const std::string& filePath) {
  ProductsRepositoryTest::shouldWriteProductsToFile(filePath);
  ProductsRepositoryTest::shouldGetAllProductsForSpecificOrderFromFile(
      filePath);
}

void testOrderRepository(const std::string& filePathForOrders,
                         const std::string& filePathForClients,
                         const std::string& filePathForProducts) {
  OrderRepositoryTest::shouldWriteOrderToFile(
      filePathForOrders, filePathForClients, filePathForProducts);
  OrderRepositoryTest::shouldGetAllOrdersFromFile(
      filePathForOrders, filePathForClients, filePathForProducts);
}

void testTablePrinter() {
  std::cout << std::endl;
  TablePrinterTest::shouldPrintVectorOfClients();
  std::cout << std::endl;

  std::cout << std::endl;
  TablePrinterTest::shouldPrintVectorOfOrders();
  std::cout << std::endl;
}
