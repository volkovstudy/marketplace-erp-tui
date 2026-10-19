#pragma once

#include "file-services/ConfigurationService.h"
#include "file-services/CsvFileService.h"
#include "models/Order.h"
#include "repositories/ClientRepository.h"
#include "repositories/ProductsRepository.h"

class OrderRepository {
 public:
  using OrderId = int;

  explicit OrderRepository(CsvFileService& csv_file_service,
                           ClientRepository& client_repo,
                           ProductsRepository& products_repo,
                           ConfigurationService& config_service);

  std::vector<Order>& getAll();
  const std::vector<Order>& getAll() const;

  OrderId save(Order order);

 private:
  std::vector<Order> orders_;

  CsvFileService& csv_file_service_;
  ClientRepository& client_repo_;
  ProductsRepository& products_repo_;
  ConfigurationService& config_service_;
};
