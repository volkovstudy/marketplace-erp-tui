#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "file-services/CsvFileService.h"
#include "repositories/ProductsRepository.h"

namespace {

namespace fs = std::filesystem;

class ProductsRepositoryTests : public ::testing::Test {
 protected:
  static inline fs::path file_;

  static void SetUpTestSuite() {
    file_ = fs::path(::testing::TempDir()) / "products-test.csv";
  }

  static void TearDownTestSuite() {
    std::error_code ec;
    fs::remove_all(file_, ec);
  }
};

}  // namespace

TEST_F(ProductsRepositoryTests, writeProductsToFile) {
  CsvFileService products_csv(file_);
  ProductsRepository productsRepository(products_csv);

  std::vector<Product> products;
  products.emplace_back("tomato", 10);
  products.emplace_back("cucumbers", 3);
  products.emplace_back("tv", 1);

  productsRepository.save(products, 1);
}

TEST_F(ProductsRepositoryTests, getAllProductsForSpecificOrderFromFile) {
  CsvFileService products_csv(file_);
  ProductsRepository productsRepository(products_csv);

  std::vector<Product> products = productsRepository.getForOrderId(1);

  ASSERT_FALSE(products.empty());
}
