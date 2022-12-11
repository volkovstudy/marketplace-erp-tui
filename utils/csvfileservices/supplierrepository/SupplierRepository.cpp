#include "SupplierRepository.h"

#include <utility>

SupplierRepository::SupplierRepository(string filePath) {
    csvFileService = new CsvFileService(std::move(filePath));
}

vector<Supplier *> SupplierRepository::getAll() {
    if (!suppliers.empty()) return suppliers;

    vector<Supplier *> result;
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

            string value = property->getValues().at(i);

            if (property->getFieldName() == "id")
                id = stoi(value);
            if (property->getFieldName() == "companyName")
                companyName = value;
        }

        auto *supplier = new Supplier(id, companyName);
        result.push_back(supplier);
    }

    suppliers = result;

    return suppliers;
}

void SupplierRepository::write(Supplier *supplier) {
    auto *id = new Property("id", {to_string(supplier->getId())});
    auto *companyName = new Property("companyName", {supplier->getCompanyName()});

    csvFileService->write({id, companyName});
}

void SupplierRepository::save(Supplier *supplier) {
    suppliers.push_back(supplier);

    write(supplier);
}
