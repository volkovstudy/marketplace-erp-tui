#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "repositories/order-repository/OrderRepository.h"

class OrderRepositoryTest {
 public:
  static void shouldWriteOrderToFile(std::string filePathForOrders,
                                     std::string filePathForClients,
                                     std::string filePathForProducts) {
    std::cout << "Saving & writing Order to " << filePathForOrders << std::endl;

    auto* clientRepository =
        new ClientRepository(std::move(filePathForClients));
    auto* productsRepository =
        new ProductsRepository(std::move(filePathForProducts));
    OrderRepository orderRepository(std::move(filePathForOrders),
                                    clientRepository, productsRepository);

    auto* client =
        new Client(2, "client for order testing", "order.testing@example.com");
    clientRepository->save(client);

    std::vector<Product*> products;
    products.push_back(new Product("playstation", 1));
    products.push_back(new Product("tv", 1));

    auto* order = new Order(2, client, products);

    orderRepository.save(order);
  }

  static void shouldGetAllOrdersFromFile(std::string filePathForOrders,
                                         std::string filePathForClients,
                                         std::string filePathForProducts) {
    std::cout << "Getting all orders from " << filePathForOrders << std::endl;

    auto* clientRepository =
        new ClientRepository(std::move(filePathForClients));
    auto* productsRepository =
        new ProductsRepository(std::move(filePathForProducts));
    OrderRepository orderRepository(std::move(filePathForOrders),
                                    clientRepository, productsRepository);

    std::vector<Order*> orders = orderRepository.getAll();

    assert(!orders.empty());
  }
};
