#include "repositories/ProductsRepository.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "file-services/CsvFileService.h"

ProductsRepository::ProductsRepository(CsvFileService& csv_file_service)
    : csv_file_service_(csv_file_service) {}

std::vector<Product> ProductsRepository::getForOrderId(int id) const {
  std::vector<Product> result;
  std::vector<Property> allLines = csv_file_service_.getAllLines();

  int maxAmountOfLines = 0;
  for (const Property& property : allLines) {
    int amountOfLines = (int)property.getValues().size();
    maxAmountOfLines = std::max(maxAmountOfLines, amountOfLines);
  }

  bool areLinesFoundForTheId = false;
  const Property* orderIdColumn;
  for (const Property& property : allLines) {
    if (property.getFieldName() == "order_id") {
      for (const std::string& value : property.getValues()) {
        if (std::stoi(value) == id) {
          areLinesFoundForTheId = true;
          orderIdColumn = &property;
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

    for (const Property& property : allLines) {
      if (property.getValues().size() < maxAmountOfLines) break;

      std::string value = property.getValues().at(i);
      std::string fieldName = property.getFieldName();

      if (fieldName == "name") name = value;
      if (fieldName == "amount") amount = stoi(value);
    }

    result.emplace_back(std::move(name), amount);
  }

  return result;
}

void ProductsRepository::save(const std::vector<Product>& products,
                              int orderId) {
  std::string orderIdString = std::to_string(orderId);

  for (auto& product : products) {
    Property name("name", {product.getName()});
    Property amount("amount", {std::to_string(product.getAmount())});
    Property orderIdProperty("order_id", {orderIdString});

    csv_file_service_.write({name, amount, orderIdProperty});
  }
}
