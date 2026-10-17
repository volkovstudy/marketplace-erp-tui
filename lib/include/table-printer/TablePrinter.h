#pragma once

#include <ostream>
#include <vector>

#include "models/Client.h"
#include "models/Order.h"

class TablePrinter {
 public:
  explicit TablePrinter(std::ostream& out);

  void print(const std::vector<Client>& clients);
  void print(const std::vector<Order>& orders);

 private:
  std::ostream& out_;
};
