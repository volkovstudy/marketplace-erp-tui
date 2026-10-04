#include "repositories/OrderRepository.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

OrderRepository::OrderRepository(std::string filePath,
                                 ClientRepository* clientRepository,
                                 ProductsRepository* productsRepository)
    : clientRepository(clientRepository),
      productsRepository(productsRepository) {
  csvFileService = new CsvFileService(std::move(filePath));
}

std::vector<Order*> OrderRepository::getAll() {
  if (!orders.empty()) return orders;

  std::vector<Order*> result;
  std::vector<Property*> allLines = csvFileService->getAllLines();

  int maxAmountOfLines = 0;
  for (Property* property : allLines) {
    int amountOfLines = (int)property->getValues().size();
    maxAmountOfLines = std::max(maxAmountOfLines, amountOfLines);
  }

  for (int i = 0; i < maxAmountOfLines; ++i) {
    int id = 0;
    Client* client;

    for (Property* property : allLines) {
      if (property->getValues().size() < maxAmountOfLines) break;

      std::string value = property->getValues().at(i);
      std::string fieldName = property->getFieldName();

      if (fieldName == "id") id = std::stoi(value);
      if (fieldName == "client_id")
        client = clientRepository->getById(std::stoi(value));
    }

    std::vector<Product*> products = productsRepository->getForOrderId(id);

    auto* order = new Order(id, client, products);
    result.push_back(order);
  }

  orders = result;

  return orders;
}

void write(Order* order, CsvFileService* csvFileService,
           ProductsRepository* productsRepository) {
  auto* id = new Property("id", {std::to_string(order->getId())});
  auto* clientId =
      new Property("client_id", {std::to_string(order->getClient()->getId())});

  csvFileService->write({id, clientId});

  productsRepository->save(order->getProducts(), order->getId());
}

void OrderRepository::save(Order* order) {
  orders.push_back(order);

  write(order, csvFileService, productsRepository);
}
