#include "Product.h"

Product::Product(const string& name, int amount) : name_(name), amount_(amount) {}

const string& Product::getName() const {
    return name_;
}

void Product::setName(const string& name) {
    name_ = name;
}

int Product::getAmount() const {
    return amount_;
}

void Product::setAmount(int amount) {
    amount_ = amount;
}
