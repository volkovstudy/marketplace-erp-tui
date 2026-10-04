#pragma once

#include <string>
#include <vector>

#include "file-services/csv-file-service/CsvFileService.h"
#include "models/product/Product.h"

class ProductsRepository {
 public:
  explicit ProductsRepository(std::string filePath);

  std::vector<Product*> getForOrderId(int id);
  void save(std::vector<Product*> products, int orderId);

 private:
  CsvFileService* csvFileService;
};
