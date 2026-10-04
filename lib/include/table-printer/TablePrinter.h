#pragma once

#include <vector>

#include "models/Client.h"
#include "models/Order.h"

class TablePrinter {
 public:
  static void printVector(const std::vector<Client*>& clients);
  static void printVector(const std::vector<Order*>& orders);
};
