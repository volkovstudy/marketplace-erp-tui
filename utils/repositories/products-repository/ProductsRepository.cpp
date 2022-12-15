#include "ProductsRepository.h"

#include <utility>

ProductsRepository::ProductsRepository(string filePath) {
    ProductsRepository::csvFileService = new CsvFileService(std::move(filePath));
}

map<string, int> ProductsRepository::getForOrderId(int id) {
    map<string, int> result;
    vector<Property *> allLines = csvFileService->getAllLines();

    int maxAmountOfLines = 0;
    for (Property *property: allLines) {
        int amountOfLines = (int) property->getValues().size();
        maxAmountOfLines = max(maxAmountOfLines, amountOfLines);
    }

    bool areLinesFoundForTheId = false;
    Property *orderIdColumn;
    for (Property *property: allLines) {
        if (property->getFieldName() == "order_id") {
            for (const string &value: property->getValues()) {
                if (stoi(value) == id) {
                    areLinesFoundForTheId = true;
                    orderIdColumn = property;
                    break;
                }
            }
            break;
        }
    }

    if (!areLinesFoundForTheId) return {};

    for (int i = 0; i < maxAmountOfLines; ++i) {
        if (stoi(orderIdColumn->getValues().at(i)) != id) break;

        string name;
        int amount;

        for (Property *property: allLines) {
            if (property->getValues().size() < maxAmountOfLines) break;

            string value = property->getValues().at(i);
            string fieldName = property->getFieldName();

            if (fieldName == "name")
                name = value;
            if (fieldName == "amount")
                amount = stoi(value);
        }

        pair<string, int> product(name, amount);
        result.insert(product);
    }

    return result;
}

void ProductsRepository::save(const map<string, int> &products, int orderId) {
    string orderIdString = to_string(orderId);

    for (auto &product: products) {
        auto *name = new Property("name", {product.first});
        auto *amount = new Property("amount", {to_string(product.second)});
        auto *orderIdProperty = new Property("order_id", {orderIdString});

        csvFileService->write({name, amount, orderIdProperty});
    }
}
