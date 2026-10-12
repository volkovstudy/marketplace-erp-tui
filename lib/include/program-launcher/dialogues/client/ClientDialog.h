#pragma once

class ClientDialog {
 public:
  void openManagementDialog();
  void addNewClient();
  void listAllClients();

 private:
  bool getChoiceAndExecuteActionAndReturnQuitResult();
};
