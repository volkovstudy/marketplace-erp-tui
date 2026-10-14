#include "repositories/OrderRepository.h"

#include <algorithm>
#include <string>
#include <vector>

#include "repositories/ClientRepository.h"
#include "repositories/ProductsRepository.h"

OrderRepository::OrderRepository(CsvFileService& csv_file_service,
                                 ClientRepository& client_repo,
                                 ProductsRepository& products_repo)
    : csv_file_service_(csv_file_service),
      client_repo_(client_repo),
      products_repo_(products_repo) {}

std::vector<Order>& OrderRepository::getAll() {
  if (!orders_.empty()) return orders_;

  std::vector<Order> result;
  std::vector<Property> allLines = csv_file_service_.getAllLines();

  int maxAmountOfLines = 0;
  for (const Property& property : allLines) {
    int amountOfLines = (int)property.getValues().size();
    maxAmountOfLines = std::max(maxAmountOfLines, amountOfLines);
  }

  for (int i = 0; i < maxAmountOfLines; ++i) {
    int id = 0;
    Client client;

    for (const Property& property : allLines) {
      if (property.getValues().size() < maxAmountOfLines) break;

      std::string value = property.getValues().at(i);
      std::string fieldName = property.getFieldName();

      if (fieldName == "id") id = std::stoi(value);
      if (fieldName == "client_id") {
        client = client_repo_.getById(std::stoi(value)).value_or(Client{});
      }
    }

    std::vector<Product> products = products_repo_.getForOrderId(id);

    result.emplace_back(id, client, products);
  }

  orders_ = result;

  return orders_;
}

void write(const Order& order, const CsvFileService& csv_file_service,
           ProductsRepository& products_repo) {
  Property id("id", {std::to_string(order.getId())});
  Property clientId("client_id", {std::to_string(order.getClient().getId())});

  csv_file_service.write({id, clientId});

  products_repo.save(order.getProducts(), order.getId());
}

void OrderRepository::save(const Order& order) {
  orders_.push_back(order);

  write(order, csv_file_service_, products_repo_);
}
