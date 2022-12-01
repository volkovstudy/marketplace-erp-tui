#ifndef MARKETPLACE_ERP_TUI_SUPPLIERREPOSITORY_H
#define MARKETPLACE_ERP_TUI_SUPPLIERREPOSITORY_H


#include "../csvfileservice/CsvFileService.h"
#include "../../../public-entities/supplier/Supplier.h"

class SupplierRepository {
private:
    CsvFileService *csvFileService;
public:
    explicit SupplierRepository(string filePath);

    vector<Supplier *> getAll();
};


#endif