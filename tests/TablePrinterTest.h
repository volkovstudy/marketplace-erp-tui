#ifndef MARKETPLACE_ERP_TUI_TESTS_TABLEPRINTERTEST_H
#define MARKETPLACE_ERP_TUI_TESTS_TABLEPRINTERTEST_H

#include "../table-printer/TablePrinter.h"

class TablePrinterTest {
public:
    static void shouldPrintVectorOfClients() {
        vector<Client*> clients;
        clients.push_back(new Client("Very long testing name", "very.long.testing.email@example.com"));
        clients.push_back(new Client("Test name", "test@example.com"));
        clients.push_back(new Client("Petr", "petya@example.com"));

        TablePrinter::printVector(clients);
    }
};

#endif
