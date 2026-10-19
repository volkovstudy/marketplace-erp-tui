#pragma once

#include <string>
#include <string_view>
#include <vector>

class Property {
 public:
  Property(std::string_view field_name, const std::vector<std::string>& values);

  void addValue(const std::string& value);

  const std::string& getFieldName() const;
  void setFieldName(std::string_view field_name);

  const std::vector<std::string>& getValues() const;
  void setValues(const std::vector<std::string>& values);

 private:
  std::string field_name_;
  std::vector<std::string> values_;
};
