#pragma once

#include <vector>

#include "models/client/Client.h"
#include "models/product/Product.h"

class Order {
 public:
  Order(Client* client, vector<Product*> products);
  Order(int id, Client* client, vector<Product*> products);

  int getId() const;
  void setId(int id);

  Client* getClient() const;
  void setClient(Client* client);

  vector<Product*> getProducts() const;
  void setProducts(vector<Product*> products);

 private:
  int id;
  Client* client;
  vector<Product*> products;
};
