#ifndef MARKETPLACE_ERP_TUI_TESTS_ORDERREPOSITORY_H
#define MARKETPLACE_ERP_TUI_TESTS_ORDERREPOSITORY_H


#include "../../models/order/Order.h"
#include "../../utils/csvfileservices/csvfileservice/CsvFileService.h"
#include "../client-repository/ClientRepository.h"
#include "../products-repository/ProductsRepository.h"

class OrderRepository {
private:
    vector<Order*> orders{};
    CsvFileService* csvFileService;
    ClientRepository* clientRepository;
    ProductsRepository* productsRepository;
public:
    explicit OrderRepository(string filePath, ClientRepository* clientRepository,
                             ProductsRepository* productsRepository);

    vector<Order*> getAll();

    void save(Order* order);
};


#endif
