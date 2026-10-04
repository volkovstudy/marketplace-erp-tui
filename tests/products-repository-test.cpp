#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "repositories/products-repository/ProductsRepository.h"

namespace fs = std::filesystem;

static const std::string kTestFilename = "products-test.csv";

class ProductsRepositoryTests : public ::testing::Test {
 protected:
  static inline fs::path file_;

  static void SetUpTestSuite() {
    file_ = fs::path(::testing::TempDir()) / kTestFilename;
  }

  static void TearDownTestSuite() {
    std::error_code ec;
    fs::remove_all(file_, ec);
  }
};

TEST_F(ProductsRepositoryTests, writeProductsToFile) {
  ProductsRepository productsRepository(file_);

  std::vector<Product*> products;
  products.push_back(new Product("tomato", 10));
  products.push_back(new Product("cucumbers", 3));
  products.push_back(new Product("tv", 1));

  productsRepository.save(products, 1);
}

TEST_F(ProductsRepositoryTests, getAllProductsForSpecificOrderFromFile) {
  ProductsRepository productsRepository(file_);

  std::vector<Product*> products = productsRepository.getForOrderId(1);

  ASSERT_FALSE(products.empty());
}
