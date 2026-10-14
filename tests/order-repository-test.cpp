#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "file-services/CsvFileService.h"
#include "repositories/ClientRepository.h"
#include "repositories/OrderRepository.h"
#include "repositories/ProductsRepository.h"

namespace fs = std::filesystem;

static const std::string kTestOrderFilename = "orders-test.csv";
static const std::string kTestClientFilename = "clients-test.csv";
static const std::string kTestProductFilename = "products-test.csv";

class OrderRepositoryTests : public ::testing::Test {
 protected:
  static inline fs::path order_file_;
  static inline fs::path client_file_;
  static inline fs::path product_file_;

  static void SetUpTestSuite() {
    order_file_ = fs::path(::testing::TempDir()) / kTestOrderFilename;
    client_file_ = fs::path(::testing::TempDir()) / kTestClientFilename;
    product_file_ = fs::path(::testing::TempDir()) / kTestProductFilename;
  }

  static void TearDownTestSuite() {
    std::error_code ec;
    fs::remove_all(order_file_, ec);
    fs::remove_all(client_file_, ec);
    fs::remove_all(product_file_, ec);
  }
};

TEST_F(OrderRepositoryTests, writeOrderToFile) {
  CsvFileService clients_csv(client_file_), products_csv(product_file_),
      orders_csv(order_file_);

  ClientRepository client_repo(clients_csv);
  ProductsRepository products_repo(products_csv);
  OrderRepository order_repo(orders_csv, client_repo, products_repo);

  Client client(2, "client for order testing", "order.testing@example.com");
  client_repo.save(client);

  std::vector<Product> products;
  products.emplace_back("playstation", 1);
  products.emplace_back("tv", 1);

  Order order(2, client, products);

  order_repo.save(order);
}

TEST_F(OrderRepositoryTests, getAllOrdersFromFile) {
  CsvFileService clients_csv(client_file_), products_csv(product_file_),
      orders_csv(order_file_);

  ClientRepository client_repo(clients_csv);
  ProductsRepository products_repo(products_csv);
  OrderRepository order_repo(orders_csv, client_repo, products_repo);

  const std::vector<Order>& orders = order_repo.getAll();

  ASSERT_FALSE(orders.empty());
}
