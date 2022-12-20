#ifndef MARKETPLACE_ERP_TUI_TESTS_TABLEPRINTERTEST_H
#define MARKETPLACE_ERP_TUI_TESTS_TABLEPRINTERTEST_H

#include "../table-printer/TablePrinter.h"

class TablePrinterTest {
public:
    static void shouldPrintVectorOfClients() {
        vector<Client*> clients = givenFourClients();

        TablePrinter::printVector(clients);
    }

    static void shouldPrintVectorOfOrders() {
        vector<Order*> orders = givenFourOrders();

        TablePrinter::printVector(orders);
    }

private:
    static vector<Client*> givenFourClients() {
        vector<Client*> clients;
        clients.push_back(new Client("Very long testing name", "very.long.testing.email@example.com"));
        clients.push_back(new Client("Very very very long name for testing class",
                                     "very.very.very.long.email.for.testing.class@example.com"));
        clients.push_back(new Client("Test name", "test@example.com"));
        clients.push_back(new Client("Petr", "petya@example.com"));

        return clients;
    }

    static vector<Order*> givenFourOrders() {
        vector<Order*> orders;
        vector<Client*> clients = givenFourClients();

        map<string, int> products1;
        products1["tomato"] = 5;
        products1["cucumbers"] = 2;
        orders.push_back(new Order(1, clients.at(0), products1));

        map<string, int> products2;
        products2["tv"] = 1;
        products2["playstation"] = 1;
        orders.push_back(new Order(2, clients.at(1), products2));

        map<string, int> products3;
        products3["table"] = 1;
        orders.push_back(new Order(3, clients.at(2), products3));

        map<string, int> products4;
        products4["Long product"] = 1000;
        orders.push_back(new Order(4, clients.at(3), products4));

        return orders;
    }
};

#endif
