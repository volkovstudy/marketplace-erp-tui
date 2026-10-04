#pragma once

#include <vector>

#include "models/client/Client.h"
#include "models/order/Order.h"

class TablePrinter {
 public:
  static void printVector(const vector<Client*>& clients);
  static void printVector(const vector<Order*>& orders);
};
