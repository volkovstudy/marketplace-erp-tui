#pragma once

#include <string>
#include <string_view>

class Product {
 public:
  Product(std::string_view name, int amount);

  const std::string& getName() const;
  void setName(std::string_view name);

  int getAmount() const;
  void setAmount(int amount);

 private:
  std::string name_;
  int amount_;
};
