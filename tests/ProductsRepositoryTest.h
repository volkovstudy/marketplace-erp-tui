#ifndef MARKETPLACE_ERP_TUI_TESTS_PRODUCTSREPOSITORYTEST_H
#define MARKETPLACE_ERP_TUI_TESTS_PRODUCTSREPOSITORYTEST_H

#include <iostream>
#include <cassert>
#include "../utils/repositories/products-repository/ProductsRepository.h"

using namespace std;

class ProductsRepositoryTest {
public:
    static void shouldWriteProductsToFile(const string &filePath) {
        cout << "Saving & writing pair<string, int> to " << filePath << endl;

        ProductsRepository productsRepository(filePath);
        map<string, int> products;
        products.insert(pair<string, int>("tomato", 10));
        products.insert(pair<string, int>("cucumbers", 3));
        products.insert(pair<string, int>("tv", 1));

        productsRepository.save(products, 1);
    }

    static void shouldGetAllProductsForSpecificOrderFromFile(const string &filePath) {
        cout << "Getting products for order with id=1 from " << filePath << endl;

        ProductsRepository productsRepository(filePath);

        map<string, int> products = productsRepository.getForOrderId(1);

        assert(!products.empty());
    }
};

#endif
