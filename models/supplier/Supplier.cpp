#include "Supplier.h"

#include <utility>

int SUPPLIER_COUNT;

Supplier::Supplier(string companyName)
        : companyName(std::move(companyName)) {
    id = ++SUPPLIER_COUNT;
}

Supplier::Supplier(int id, string companyName)
        : id(id),
          companyName(std::move(companyName)) {}

const string &Supplier::getCompanyName() const {
    return companyName;
}

void Supplier::setCompanyName(const string &companyName) {
    Supplier::companyName = companyName;
}

int Supplier::getId() const {
    return id;
}

void Supplier::setId(int id) {
    Supplier::id = id;
}
