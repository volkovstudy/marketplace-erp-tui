#ifndef MARKETPLACE_ERP_TUI_ORDER_H
#define MARKETPLACE_ERP_TUI_ORDER_H


#include <map>
#include "../client/Client.h"
#include "../product/Product.h"

class Order {
private:
    int id;
    Client *client;
    map<Product, int> products;
public:
    Order(Client *client, const map<Product, int> &products);

    int getId() const;
    void setId(int id);

    Client *getClient() const;
    void setClient(Client *client);

    const map<Product, int> &getProducts() const;
    void setProducts(const map<Product, int> &products);
};


#endif
