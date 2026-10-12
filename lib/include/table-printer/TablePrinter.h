#pragma once

#include <vector>

#include "models/Client.h"
#include "models/Order.h"

class TablePrinter {
 public:
  void printVector(const std::vector<Client*>& clients);
  void printVector(const std::vector<Order*>& orders);
};
