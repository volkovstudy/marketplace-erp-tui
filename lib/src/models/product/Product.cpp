#include "models/product/Product.h"

#include <string>

Product::Product(const std::string& name, int amount)
    : name_(name), amount_(amount) {}

const std::string& Product::getName() const { return name_; }

void Product::setName(const std::string& name) { name_ = name; }

int Product::getAmount() const { return amount_; }

void Product::setAmount(int amount) { amount_ = amount; }
