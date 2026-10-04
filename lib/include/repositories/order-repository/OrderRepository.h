#pragma once

#include "file-services/csv-file-service/CsvFileService.h"
#include "models/order/Order.h"
#include "repositories/client-repository/ClientRepository.h"
#include "repositories/products-repository/ProductsRepository.h"

class OrderRepository {
 public:
  explicit OrderRepository(string filePath, ClientRepository* clientRepository,
                           ProductsRepository* productsRepository);

  vector<Order*> getAll();
  void save(Order* order);

 private:
  vector<Order*> orders{};
  CsvFileService* csvFileService;
  ClientRepository* clientRepository;
  ProductsRepository* productsRepository;
};
