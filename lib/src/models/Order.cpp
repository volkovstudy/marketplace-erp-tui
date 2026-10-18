#include "models/Order.h"

#include <vector>

#include "file-services/ConfigurationService.h"
#include "models/Client.h"
#include "models/Product.h"

Order::Order(const Client& client, const std::vector<Product>& products)
    : client_(client), products_(products) {
  ConfigurationService* configurationService =
      ConfigurationService::getInstance(
          ConfigurationService::getMainConfigFilePath());

  id_ = configurationService->getNextId();
  configurationService->save();
}

Order::Order(int id, const Client& client, const std::vector<Product>& products)
    : id_(id), client_(client), products_(products) {}

int Order::getId() const { return id_; }

void Order::setId(int id) { id_ = id; }

Client Order::getClient() const { return client_; }

void Order::setClient(const Client& client) { client_ = client; }

const std::vector<Product>& Order::getProducts() const { return products_; }

void Order::setProducts(const std::vector<Product>& products) {
  products_ = products;
}
