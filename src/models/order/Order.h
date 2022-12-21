#ifndef MARKETPLACE_ERP_TUI_ORDER_H
#define MARKETPLACE_ERP_TUI_ORDER_H


#include <map>
#include "../client/Client.h"

class Order {
private:
    int id;
    Client* client;
    map<string, int> products;
public:
    Order(Client* client, const map<string, int>& products);

    Order(int id, Client* client, const map<string, int>& products);

    int getId() const;

    void setId(int id);

    Client* getClient() const;

    void setClient(Client* client);

    const map<string, int>& getProducts() const;

    void setProducts(const map<string, int>& products);
};


#endif
