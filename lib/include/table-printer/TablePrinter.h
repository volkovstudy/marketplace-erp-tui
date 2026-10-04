#pragma once

#include <vector>

#include "models/client/Client.h"
#include "models/order/Order.h"

class TablePrinter {
 public:
  static void printVector(const std::vector<Client*>& clients);
  static void printVector(const std::vector<Order*>& orders);
};
