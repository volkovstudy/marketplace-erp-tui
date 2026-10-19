#pragma once

#include "repositories/ClientRepository.h"
#include "repositories/OrderRepository.h"

class OrderAddingDialog {
 public:
  explicit OrderAddingDialog(OrderRepository& orders_repo,
                             ClientRepository& clients_repo);

  void addOrder();

 private:
  OrderRepository& orders_repo_;
  ClientRepository& clients_repo_;
};
