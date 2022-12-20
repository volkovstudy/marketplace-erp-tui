#ifndef MARKETPLACE_ERP_TUI_TESTS_TABLEPRINTER_H
#define MARKETPLACE_ERP_TUI_TESTS_TABLEPRINTER_H


#include <vector>
#include "../models/client/Client.h"
#include "../models/order/Order.h"

class TablePrinter {
public:
    static void printVector(const vector<Client*>& clients);

    static void printVector(const vector<Order*>& orders);
};


#endif
