#pragma once

#include <istream>
#include <ostream>
#include <string>

#include "models/Client.h"
#include "repositories/ClientRepository.h"

class ClientAddingDialog {
 public:
  explicit ClientAddingDialog(std::ostream& out, std::istream& in,
                              ClientRepository& repo);

  void addClient();

 private:
  Client readClientDetails();

  std::ostream& out_;
  std::istream& in_;

  ClientRepository& repo_;
};
