#ifndef MARKETPLACE_ERP_TUI_TESTS_TABLEPRINTERTEST_H
#define MARKETPLACE_ERP_TUI_TESTS_TABLEPRINTERTEST_H

#include "../src/table-printer/TablePrinter.h"

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

        vector<Product*> products1;
        products1.push_back(new Product("tomato", 5));
        products1.push_back(new Product("cucumbers", 2));
        orders.push_back(new Order(1, clients.at(0), products1));

        vector<Product*> products2;
        products2.push_back(new Product("tv", 1));
        products2.push_back(new Product("playstation", 1));
        orders.push_back(new Order(2, clients.at(1), products2));

        vector<Product*> products3;
        products3.push_back(new Product("table", 1));
        orders.push_back(new Order(3, clients.at(2), products3));

        vector<Product*> products4;
        products4.push_back(new Product("Long product", 1000));
        orders.push_back(new Order(4, clients.at(3), products4));

        return orders;
    }
};

#endif
