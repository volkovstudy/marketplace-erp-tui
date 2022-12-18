#ifndef MARKETPLACE_ERP_TUI_TESTS_ORDERREPOSITORYTEST_H
#define MARKETPLACE_ERP_TUI_TESTS_ORDERREPOSITORYTEST_H


#include <iostream>
#include <utility>
#include <cassert>
#include "../repositories/order-repository/OrderRepository.h"

using namespace std;

class OrderRepositoryTest {
public:
    static void
    shouldWriteOrderToFile(string filePathForOrders, string filePathForClients, string filePathForProducts) {
        cout << "Saving & writing Order to " << filePathForOrders << endl;

        auto* clientRepository = new ClientRepository(std::move(filePathForClients));
        auto* productsRepository = new ProductsRepository(std::move(filePathForProducts));
        OrderRepository orderRepository(std::move(filePathForOrders), clientRepository, productsRepository);

        auto* client = new Client(2, "client for order testing", "order.testing@example.com");
        clientRepository->save(client);

        map<string, int> products;
        products.insert(pair<string, int>("playstation", 1));
        products.insert(pair<string, int>("tv", 1));

        auto* order = new Order(2, client, products);

        orderRepository.save(order);
    }

    static void
    shouldGetAllOrdersFromFile(string filePathForOrders, string filePathForClients, string filePathForProducts) {
        cout << "Getting all orders from " << filePathForOrders << endl;

        auto* clientRepository = new ClientRepository(std::move(filePathForClients));
        auto* productsRepository = new ProductsRepository(std::move(filePathForProducts));
        OrderRepository orderRepository(std::move(filePathForOrders), clientRepository, productsRepository);

        vector<Order*> orders = orderRepository.getAll();

        assert(!orders.empty());
    }
};


#endif
