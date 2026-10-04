#include "models/Order.h"

#include <vector>

#include "file-services/ConfigurationService.h"

Order::Order(Client* client, std::vector<Product*> products)
    : client(client), products(products) {
  ConfigurationService* configurationService =
      ConfigurationService::getInstance(
          ConfigurationService::getMainConfigFilePath());

  id = configurationService->getNextId();
  configurationService->save();
}

Order::Order(int id, Client* client, std::vector<Product*> products)
    : id(id), client(client), products(products) {}

int Order::getId() const { return id; }

void Order::setId(int id) { Order::id = id; }

Client* Order::getClient() const { return client; }

void Order::setClient(Client* client) { Order::client = client; }

std::vector<Product*> Order::getProducts() const { return products; }

void Order::setProducts(std::vector<Product*> products) {
  Order::products = products;
}
