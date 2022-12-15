#ifndef MARKETPLACE_ERP_TUI_TESTS_SUPPLIERREPOSITORY_H
#define MARKETPLACE_ERP_TUI_TESTS_SUPPLIERREPOSITORY_H

#include <cassert>
#include <utility>
#include <iostream>

#include "../utils/repositories/supplier-repository/SupplierRepository.h"

using namespace std;

class SupplierRepositoryTest {
public:
    static void shouldWriteSupplierToFile(string filePath) {
        cout << "Saving & writing Supplier to " << filePath << endl;

        SupplierRepository supplierRepository(std::move(filePath));
        auto *supplier = new Supplier(1, "test company");

        supplierRepository.save(supplier);
    }

    static void shouldGetAllSuppliersFromFile(string filePath) {
        cout << "Getting all suppliers from " << filePath << endl;

        SupplierRepository supplierRepository(std::move(filePath));

        vector<Supplier *> suppliers = supplierRepository.getAll();

        assert(!suppliers.empty());
    }
};

#endif
