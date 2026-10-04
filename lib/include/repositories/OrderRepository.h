#pragma once

#include "file-services/CsvFileService.h"
#include "models/Order.h"
#include "repositories/ClientRepository.h"
#include "repositories/ProductsRepository.h"

class OrderRepository {
 public:
  explicit OrderRepository(std::string filePath,
                           ClientRepository* clientRepository,
                           ProductsRepository* productsRepository);

  std::vector<Order*> getAll();
  void save(Order* order);

 private:
  std::vector<Order*> orders{};
  CsvFileService* csvFileService;
  ClientRepository* clientRepository;
  ProductsRepository* productsRepository;
};
