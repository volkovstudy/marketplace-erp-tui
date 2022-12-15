#ifndef MARKETPLACE_ERP_TUI_TESTS_ORDERREPOSITORY_H
#define MARKETPLACE_ERP_TUI_TESTS_ORDERREPOSITORY_H


#include "../../../public-entities/order/Order.h"
#include "../../csvfileservices/csvfileservice/CsvFileService.h"
#include "../client-repository/ClientRepository.h"

class OrderRepository {
private:
    vector<Order *> orders{};
    CsvFileService *csvFileService;
    ClientRepository *clientRepository;
public:
    explicit OrderRepository(string filePath, ClientRepository *clientRepository);

    vector<Order *> getAll();

    void save(Order *order);
};


#endif
