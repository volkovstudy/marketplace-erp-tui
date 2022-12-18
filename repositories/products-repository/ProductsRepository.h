#ifndef MARKETPLACE_ERP_TUI_TESTS_PRODUCTSREPOSITORY_H
#define MARKETPLACE_ERP_TUI_TESTS_PRODUCTSREPOSITORY_H


#include <map>
#include "../../file-services/csvfileservice/CsvFileService.h"

class ProductsRepository {
private:
    CsvFileService* csvFileService;
public:
    explicit ProductsRepository(string filePath);

    map<string, int> getForOrderId(int id);

    void save(const map<string, int>& products, int orderId);
};


#endif
