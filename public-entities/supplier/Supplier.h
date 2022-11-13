#ifndef MARKETPLACE_ERP_TUI_STORAGE_SUPPLIER_H
#define MARKETPLACE_ERP_TUI_STORAGE_SUPPLIER_H

#include <string>

using namespace std;

class Supplier {
private:
    string companyName;
public:
    explicit Supplier(string companyName);

    const string &getCompanyName() const;

    void setCompanyName(const string &companyName);
};


#endif
