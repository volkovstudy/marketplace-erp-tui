#pragma once

#include <string>

class Product {
 public:
  Product(const std::string& name, int amount);

  const std::string& getName() const;
  void setName(const std::string& name);

  int getAmount() const;
  void setAmount(int amount);

 private:
  std::string name_;
  int amount_;
};
