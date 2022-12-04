#ifndef MARKETPLACE_ERP_TUI_TESTS_SUPPLIERREPOSITORY_H
#define MARKETPLACE_ERP_TUI_TESTS_SUPPLIERREPOSITORY_H

#include <utility>
#include <iostream>

#include "../utils/csvfileservices/supplierrepository/SupplierRepository.h"

using namespace std;

class SupplierRepositoryTest {
public:
    static void shouldWriteSupplierToFile(string filePath) {
        cout << "Writing Supplier to " << filePath << endl;

        SupplierRepository supplierRepository(std::move(filePath));
        auto *supplier = new Supplier(1, "test company");

        supplierRepository.write(supplier);
    }
};

#endif
