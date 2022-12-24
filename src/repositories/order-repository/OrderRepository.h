#ifndef MARKETPLACE_ERP_TUI_TESTS_ORDERREPOSITORY_H
#define MARKETPLACE_ERP_TUI_TESTS_ORDERREPOSITORY_H


#include "../../models/order/Order.h"
#include "../../file-services/csv-file-service/CsvFileService.h"
#include "../client-repository/ClientRepository.h"
#include "../products-repository/ProductsRepository.h"

class OrderRepository {
public:
    explicit OrderRepository(string filePath,
                             ClientRepository* clientRepository,
                             ProductsRepository* productsRepository
    );

    vector<Order*> getAll();
    void save(Order* order);
private:
    vector<Order*> orders{};
    CsvFileService* csvFileService;
    ClientRepository* clientRepository;
    ProductsRepository* productsRepository;
};


#endif
