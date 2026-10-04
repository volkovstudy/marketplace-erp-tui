#ifndef MARKETPLACE_ERP_TUI_PRODUCT_H
#define MARKETPLACE_ERP_TUI_PRODUCT_H

#include <string>

using namespace std;

class Product {
public:
    Product(const string& name, int amount);

    const string& getName() const;
    void setName(const string& name);

    int getAmount() const;
    void setAmount(int amount);
private:
    string name_;
    int amount_;
};


#endif
