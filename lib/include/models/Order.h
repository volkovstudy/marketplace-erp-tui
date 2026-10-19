#pragma once

#include <vector>

#include "models/Client.h"
#include "models/Product.h"

class Order {
 public:
  Order() = default;
  Order(const Client& client, const std::vector<Product>& products);
  Order(int id, const Client& client, const std::vector<Product>& products);

  int getId() const;
  void setId(int id);

  Client getClient() const;
  void setClient(const Client& client);

  const std::vector<Product>& getProducts() const;
  void setProducts(const std::vector<Product>& products);

 private:
  int id_ = -1;
  Client client_{};
  std::vector<Product> products_{};
};
