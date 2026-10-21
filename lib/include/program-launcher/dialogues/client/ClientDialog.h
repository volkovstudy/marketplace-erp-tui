#pragma once

#include <istream>
#include <ostream>

#include "repositories/ClientRepository.h"

class ClientDialog {
 public:
  explicit ClientDialog(std::ostream& out, std::istream& in,
                        ClientRepository& repo);

  void openManagement();
  void addNewClient();
  void listAllClients();

 private:
  bool handleUserChoice();

  std::ostream& out_;
  std::istream& in_;

  ClientRepository& repo_;
};
