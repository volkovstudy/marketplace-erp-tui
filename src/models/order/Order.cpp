#include "Order.h"
#include "../../file-services/configuration-service/ConfigurationService.h"

Order::Order(Client* client, const map<string, int>& products) :
        client(client),
        products(products) {
    ConfigurationService* configurationService = ConfigurationService::getInstance(
            ConfigurationService::getMainConfigFilePath());

    id = configurationService->getNextId();
    configurationService->save();
}

Order::Order(int id, Client* client, const map<string, int>& products) :
        id(id),
        client(client),
        products(products) {}

int Order::getId() const {
    return id;
}

void Order::setId(int id) {
    Order::id = id;
}

Client* Order::getClient() const {
    return client;
}

void Order::setClient(Client* client) {
    Order::client = client;
}

const map<string, int>& Order::getProducts() const {
    return products;
}

void Order::setProducts(const map<string, int>& products) {
    Order::products = products;
}
