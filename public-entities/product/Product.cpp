#include "Product.h"

#include <utility>

int PRODUCT_COUNT;

Product::Product(string name, Category *category) :
                                    name(std::move(name)),
                                    category(category) {
    id = ++PRODUCT_COUNT;
}

int Product::getId() const {
    return id;
}

void Product::setId(int id) {
    Product::id = id;
}

const string &Product::getName() const {
    return name;
}

void Product::setName(const string &name) {
    Product::name = name;
}

Category *Product::getCategory() const {
    return category;
}

void Product::setCategory(Category *category) {
    Product::category = category;
}
