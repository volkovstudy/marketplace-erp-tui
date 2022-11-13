#include "Order.h"

int ORDER_COUNT;

Order::Order(Client *client, const map<Product, int> &products) :
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

const map<Product, int> &Order::getProducts() const {
    return products;
}

void Order::setProducts(const map<Product, int> &products) {
    Order::products = products;
}
