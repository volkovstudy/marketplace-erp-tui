#ifndef MARKETPLACE_ERP_TUI_STORAGE_SUPPLIER_H
#define MARKETPLACE_ERP_TUI_STORAGE_SUPPLIER_H

#include <string>

using namespace std;

class Supplier {
private:
    int id;
    string companyName;
public:
    explicit Supplier(string companyName);

    Supplier(int id, string companyName);

    int getId() const;
    void setId(int id);

    const string &getCompanyName() const;
    void setCompanyName(const string &companyName);
};


#endif
