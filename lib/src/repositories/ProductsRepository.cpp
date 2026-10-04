#include "repositories/ProductsRepository.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

ProductsRepository::ProductsRepository(std::string filePath) {
  ProductsRepository::csvFileService = new CsvFileService(std::move(filePath));
}

std::vector<Product*> ProductsRepository::getForOrderId(int id) {
  std::vector<Product*> result;
  std::vector<Property*> allLines = csvFileService->getAllLines();

  int maxAmountOfLines = 0;
  for (Property* property : allLines) {
    int amountOfLines = (int)property->getValues().size();
    maxAmountOfLines = std::max(maxAmountOfLines, amountOfLines);
  }

  bool areLinesFoundForTheId = false;
  Property* orderIdColumn;
  for (Property* property : allLines) {
    if (property->getFieldName() == "order_id") {
      for (const std::string& value : property->getValues()) {
        if (std::stoi(value) == id) {
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

    std::string name;
    int amount;

    for (Property* property : allLines) {
      if (property->getValues().size() < maxAmountOfLines) break;

      std::string value = property->getValues().at(i);
      std::string fieldName = property->getFieldName();

      if (fieldName == "name") name = value;
      if (fieldName == "amount") amount = stoi(value);
    }

    Product* product = new Product(name, amount);
    result.push_back(product);
  }

  return result;
}

void ProductsRepository::save(std::vector<Product*> products, int orderId) {
  std::string orderIdString = std::to_string(orderId);

  for (Product* product : products) {
    auto* name = new Property("name", {product->getName()});
    auto* amount =
        new Property("amount", {std::to_string(product->getAmount())});
    auto* orderIdProperty = new Property("order_id", {orderIdString});

    csvFileService->write({name, amount, orderIdProperty});
  }
}
