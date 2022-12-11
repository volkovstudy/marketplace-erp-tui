#ifndef MARKETPLACE_ERP_TUI_SUPPLIERREPOSITORY_H
#define MARKETPLACE_ERP_TUI_SUPPLIERREPOSITORY_H


#include "../csvfileservice/CsvFileService.h"
#include "../../../public-entities/supplier/Supplier.h"

class SupplierRepository {
private:
    vector<Supplier *> suppliers{};
public:
    explicit SupplierRepository(string filePath);

    vector<Supplier *> getAll();

    void write(Supplier *supplier);

    void save(Supplier *supplier);
};


#endif
