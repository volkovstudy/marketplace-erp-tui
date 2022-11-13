#include "Supplier.h"

#include <utility>

Supplier::Supplier(string companyName) : companyName(std::move(companyName)) {}

const string &Supplier::getCompanyName() const {
    return companyName;
}

void Supplier::setCompanyName(const string &companyName) {
    Supplier::companyName = companyName;
}
