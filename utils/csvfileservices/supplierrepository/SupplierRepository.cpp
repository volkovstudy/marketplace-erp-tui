#include "SupplierRepository.h"

#include <utility>

SupplierRepository::SupplierRepository(string filePath) {
    csvFileService = new CsvFileService(std::move(filePath));
}

vector<Supplier *> SupplierRepository::getAll() {
    vector<Supplier *> suppliers;
    vector<Property *> allLines = csvFileService->getAllLines();

    int maxAmountOfLines = 0;
    for (Property *property: allLines) {
        int amountOfLines = (int) property->getValues().size();
        maxAmountOfLines = max(maxAmountOfLines, amountOfLines);
    }

    for (int i = 0; i < maxAmountOfLines; ++i) {
        int id = 0;
        string companyName;

        for (Property *property: allLines) {
            if (property->getValues().size() < maxAmountOfLines) break;

            if (property->getFieldName() == "id")
                id = stoi(property->getValues().at(i));
            if (property->getFieldName() == "companyName")
                companyName = property->getValues().at(i);
        }

        auto *supplier = new Supplier(id, companyName);
        suppliers.push_back(supplier);
    }

    return suppliers;
}

void SupplierRepository::write(Supplier *supplier) {
    auto *id = new Property("id", {to_string(supplier->getId())});
    auto *companyName = new Property("companyName", {supplier->getCompanyName()});

    csvFileService->write({id, companyName});
}
