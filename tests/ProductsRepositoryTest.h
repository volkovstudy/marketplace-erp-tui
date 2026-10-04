#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "repositories/products-repository/ProductsRepository.h"

class ProductsRepositoryTest {
 public:
  static void shouldWriteProductsToFile(const std::string& filePath) {
    std::cout << "Saving & writing pair<string, int> to " << filePath
              << std::endl;

    ProductsRepository productsRepository(filePath);
    std::vector<Product*> products;
    products.push_back(new Product("tomato", 10));
    products.push_back(new Product("cucumbers", 3));
    products.push_back(new Product("tv", 1));

    productsRepository.save(products, 1);
  }

  static void shouldGetAllProductsForSpecificOrderFromFile(
      const std::string& filePath) {
    std::cout << "Getting products for order with id=1 from " << filePath
              << std::endl;

    ProductsRepository productsRepository(filePath);

    std::vector<Product*> products = productsRepository.getForOrderId(1);

    assert(!products.empty());
  }
};
