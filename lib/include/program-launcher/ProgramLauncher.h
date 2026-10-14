#pragma once

#include <istream>
#include <ostream>
#include <string>

#include "file-services/CsvFileService.h"
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

  CsvFileService client_csv_{kPathToClientsFile};
  ClientRepository client_repo_{client_csv_};
};
