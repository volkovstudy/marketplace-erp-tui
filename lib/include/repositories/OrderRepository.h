#pragma once

#include "file-services/CsvFileService.h"
#include "models/Order.h"
#include "repositories/ClientRepository.h"
#include "repositories/ProductsRepository.h"

class OrderRepository {
 public:
  explicit OrderRepository(CsvFileService& csv_file_service,
                           ClientRepository& client_repo,
                           ProductsRepository& products_repo);

  std::vector<Order>& getAll();

  void save(const Order& order);

 private:
  std::vector<Order> orders_{};

  CsvFileService& csv_file_service_;
  ClientRepository& client_repo_;
  ProductsRepository& products_repo_;
};
