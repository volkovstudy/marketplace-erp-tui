#include "ProductsRepository.h"

#include <utility>

ProductsRepository::ProductsRepository(string filePath) {
    ProductsRepository::csvFileService = new CsvFileService(std::move(filePath));
}

vector<Product*> ProductsRepository::getForOrderId(int id) {
    vector<Product*> result;
    vector<Property*> allLines = csvFileService->getAllLines();

    int maxAmountOfLines = 0;
    for (Property* property: allLines) {
        int amountOfLines = (int) property->getValues().size();
        maxAmountOfLines = max(maxAmountOfLines, amountOfLines);
    }

    bool areLinesFoundForTheId = false;
    Property* orderIdColumn;
    for (Property* property: allLines) {
        if (property->getFieldName() == "order_id") {
            for (const string& value: property->getValues()) {
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
        if (stoi(orderIdColumn->getValues().at(i)) != id) continue;

        string name;
        int amount;

        for (Property* property: allLines) {
            if (property->getValues().size() < maxAmountOfLines) break;

            string value = property->getValues().at(i);
            string fieldName = property->getFieldName();

            if (fieldName == "name")
                name = value;
            if (fieldName == "amount")
                amount = stoi(value);
        }

        Product* product = new Product(name, amount);
        result.push_back(product);
    }

    return result;
}

void ProductsRepository::save(vector<Product*> products, int orderId) {
    string orderIdString = to_string(orderId);

    for (Product* product: products) {
        auto* name = new Property("name", {product->getName()});
        auto* amount = new Property("amount", {to_string(product->getAmount())});
        auto* orderIdProperty = new Property("order_id", {orderIdString});

        csvFileService->write({name, amount, orderIdProperty});
    }
}
