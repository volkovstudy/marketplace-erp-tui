#ifndef MARKETPLACE_ERP_TUI_PRODUCT_H
#define MARKETPLACE_ERP_TUI_PRODUCT_H


#include <string>
#include "../category/Category.h"

using namespace std;

class Product {
private:
    int id;
    string name;
    Category *category;
public:
    Product(string name, Category *category);

    int getId() const;
    void setId(int id);

    const string &getName() const;
    void setName(const string &name);

    Category *getCategory() const;
    void setCategory(Category *category);
};


#endif
