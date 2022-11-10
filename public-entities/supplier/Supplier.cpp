#include "Supplier.h"

Supplier::Supplier(const string &companyName) : companyName(companyName) {}

const string &Supplier::getCompanyName() const {
    return companyName;
}

void Supplier::setCompanyName(const string &companyName) {
    Supplier::companyName = companyName;
}
