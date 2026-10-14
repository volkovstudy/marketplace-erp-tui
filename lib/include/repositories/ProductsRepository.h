#pragma once

#include <vector>

#include "file-services/CsvFileService.h"
#include "models/Product.h"

class ProductsRepository {
 public:
  explicit ProductsRepository(CsvFileService& csv_file_service);

  std::vector<Product> getForOrderId(int id) const;
  void save(const std::vector<Product>& products, int order_id);

 private:
  CsvFileService& csv_file_service_;
};
