#pragma once

class OrdersDialog {
 public:
  void openManagementDialog();
  void addNewOrder();
  void listAllOrders();

 private:
  bool getChoiceAndExecuteActionAndReturnQuitResult();
};
