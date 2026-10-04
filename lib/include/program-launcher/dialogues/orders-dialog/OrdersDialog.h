#pragma once

class OrdersDialog {
 public:
  static void openManagementDialog();
  static void addNewOrder();
  static void listAllOrders();

 private:
  static void printSectionVariants();
  static bool getChoiceAndExecuteActionAndReturnQuitResult();
};
