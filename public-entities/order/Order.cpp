#include "Order.h"

int ORDER_COUNT;

Order::Order(Client *client, const map<string, int> &products) :
        client(client),
        products(products) {
    id = ++ORDER_COUNT;
}

int Order::getId() const {
    return id;
}

void Order::setId(int id) {
    Order::id = id;
}

Client *Order::getClient() const {
    return client;
}

void Order::setClient(Client *client) {
    Order::client = client;
}

const map<string, int> &Order::getProducts() const {
    return products;
}

void Order::setProducts(const map<string, int> &products) {
    Order::products = products;
}
