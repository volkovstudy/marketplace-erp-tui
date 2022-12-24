#ifndef MARKETPLACE_ERP_TUI_TESTS_PRODUCTSREPOSITORYTEST_H
#define MARKETPLACE_ERP_TUI_TESTS_PRODUCTSREPOSITORYTEST_H

#include <iostream>
#include <cassert>
#include "../src/repositories/products-repository/ProductsRepository.h"

using namespace std;

class ProductsRepositoryTest {
public:
    static void shouldWriteProductsToFile(const string& filePath) {
        cout << "Saving & writing pair<string, int> to " << filePath << endl;

        ProductsRepository productsRepository(filePath);
        vector<Product*> products;
        products.push_back(new Product("tomato", 10));
        products.push_back(new Product("cucumbers", 3));
        products.push_back(new Product("tv", 1));

        productsRepository.save(products, 1);
    }

    static void shouldGetAllProductsForSpecificOrderFromFile(const string& filePath) {
        cout << "Getting products for order with id=1 from " << filePath << endl;

        ProductsRepository productsRepository(filePath);

        vector<Product*> products = productsRepository.getForOrderId(1);

        assert(!products.empty());
    }
};

#endif
