#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "repositories/OrderRepository.h"

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
  auto* clientRepository = new ClientRepository(client_file_);
  auto* productsRepository = new ProductsRepository(product_file_);
  OrderRepository orderRepository(order_file_, clientRepository,
                                  productsRepository);

  auto* client =
      new Client(2, "client for order testing", "order.testing@example.com");
  clientRepository->save(client);

  std::vector<Product*> products;
  products.push_back(new Product("playstation", 1));
  products.push_back(new Product("tv", 1));

  auto* order = new Order(2, client, products);

  orderRepository.save(order);
}

TEST_F(OrderRepositoryTests, getAllOrdersFromFile) {
  auto* clientRepository = new ClientRepository(client_file_);
  auto* productsRepository = new ProductsRepository(product_file_);
  OrderRepository orderRepository(order_file_, clientRepository,
                                  productsRepository);

  std::vector<Order*> orders = orderRepository.getAll();

  ASSERT_FALSE(orders.empty());
}
