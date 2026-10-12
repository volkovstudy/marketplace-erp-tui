#pragma once

#include <istream>
#include <ostream>

#include "repositories/ClientRepository.h"

const static std::string kPathToClientsFile = "marketplace-erp/clients.csv";

class ProgramLauncher {
 public:
  explicit ProgramLauncher(std::ostream& out, std::istream& in);

  void start();

 private:
  void printProgramSections();
  bool handleUserChoice();

  std::ostream& out_;
  std::istream& in_;

  ClientRepository client_repo_{kPathToClientsFile};
};
