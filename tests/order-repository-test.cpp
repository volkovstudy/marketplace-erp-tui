#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "file-services/ConfigurationService.h"
#include "file-services/CsvFileService.h"
#include "repositories/ClientRepository.h"
#include "repositories/OrderRepository.h"
#include "repositories/ProductsRepository.h"

namespace {

namespace fs = std::filesystem;

class OrderRepositoryTests : public ::testing::Test {
 protected:
  static inline fs::path dir_;
  static inline fs::path order_file_;
  static inline fs::path client_file_;
  static inline fs::path product_file_;
  static inline fs::path config_file_;

  static void SetUpTestSuite() {
    dir_ = fs::path(::testing::TempDir()) / "marketplace_erp_tui_tests";

    std::error_code ec;
    fs::create_directories(dir_, ec);
    ASSERT_FALSE(ec) << "Cannot create " << dir_ << ": " << ec.message();

    order_file_ = dir_ / "orders-test.csv";
    client_file_ = dir_ / "clients-test.csv";
    product_file_ = dir_ / "products-test.csv";
    config_file_ = dir_ / "config-test.csv";
  }

  static void TearDownTestSuite() {
    std::error_code ec;
    fs::remove_all(dir_, ec);
  }
};

}  // namespace

TEST_F(OrderRepositoryTests, writeOrderToFile) {
  CsvFileService clients_csv(client_file_), config_csv(config_file_),
      products_csv(product_file_), orders_csv(order_file_);

  ConfigurationService config_service(config_csv);
  ClientRepository client_repo(clients_csv, config_service);
  ProductsRepository products_repo(products_csv);
  OrderRepository order_repo(orders_csv, client_repo, products_repo,
                             config_service);

  Client client(2, "client for order testing", "order.testing@example.com");
  client_repo.save(client);

  std::vector<Product> products;
  products.emplace_back("playstation", 1);
  products.emplace_back("tv", 1);

  Order order(2, client, products);

  order_repo.save(order);
}

TEST_F(OrderRepositoryTests, getAllOrdersFromFile) {
  CsvFileService clients_csv(client_file_), config_csv(config_file_),
      products_csv(product_file_), orders_csv(order_file_);

  ConfigurationService config_service(config_csv);
  ClientRepository client_repo(clients_csv, config_service);
  ProductsRepository products_repo(products_csv);
  OrderRepository order_repo(orders_csv, client_repo, products_repo,
                             config_service);

  const std::vector<Order>& orders = order_repo.getAll();

  ASSERT_FALSE(orders.empty());
}
