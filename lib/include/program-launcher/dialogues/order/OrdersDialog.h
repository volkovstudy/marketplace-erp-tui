#pragma once

#include "repositories/OrderRepository.h"
#include "repositories/ClientRepository.h"

class OrdersDialog {
 public:
  explicit OrdersDialog(OrderRepository& orders_repo, ClientRepository& clients_repo);

  void openManagementDialog();
  void addNewOrder();
  void listAllOrders();

 private:
  bool getChoiceAndExecuteActionAndReturnQuitResult();

  OrderRepository& orders_repo_;
  ClientRepository& clients_repo_;
};
