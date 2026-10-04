#pragma once

class ClientDialog {
 public:
  static void openManagementDialog();
  static void addNewClient();
  static void listAllClients();

 private:
  static void printSectionVariants();
  static bool getChoiceAndExecuteActionAndReturnQuitResult();
};
