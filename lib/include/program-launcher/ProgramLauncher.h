#pragma once

#include <istream>
#include <ostream>
#include <string>

#include "file-services/ConfigurationService.h"
#include "file-services/CsvFileService.h"
#include "repositories/ClientRepository.h"
#include "repositories/OrderRepository.h"
#include "repositories/ProductsRepository.h"

static const std::string kConfigFile = "marketplace-erp/config.csv";
static const std::string kClientsFile = "marketplace-erp/clients.csv";
static const std::string kProductsFile = "marketplace-erp/products.csv";
static const std::string kOrdersFile = "marketplace-erp/orders.csv";

class ProgramLauncher {
 public:
  explicit ProgramLauncher(std::ostream& out, std::istream& in);

  void start();

 private:
  void printProgramSections();
  bool handleUserChoice();

  std::ostream& out_;
  std::istream& in_;

  CsvFileService config_csv_{kConfigFile};
  ConfigurationService config_service_{config_csv_};

  CsvFileService clients_csv_{kClientsFile};
  ClientRepository clients_repo_{clients_csv_, config_service_};

  CsvFileService products_csv_{kProductsFile};
  ProductsRepository products_repo_{products_csv_};

  CsvFileService orders_csv_{kOrdersFile};
  OrderRepository orders_repo_{orders_csv_, clients_repo_, products_repo_,
                               config_service_};
};
