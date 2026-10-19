#include "models/Product.h"

#include <string>
#include <string_view>

Product::Product(std::string_view name, int amount)
    : name_(name), amount_(amount) {}

const std::string& Product::getName() const { return name_; }

void Product::setName(std::string_view name) { name_ = name; }

int Product::getAmount() const { return amount_; }

void Product::setAmount(int amount) { amount_ = amount; }
