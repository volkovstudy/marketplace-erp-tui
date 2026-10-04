#pragma once

#include <map>

#include "file-services/csv-file-service/CsvFileService.h"
#include "models/product/Product.h"

class ProductsRepository {
 public:
  explicit ProductsRepository(string filePath);

  vector<Product*> getForOrderId(int id);
  void save(vector<Product*> products, int orderId);

 private:
  CsvFileService* csvFileService;
};
