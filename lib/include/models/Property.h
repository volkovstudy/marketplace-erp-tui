#pragma once

#include <string>
#include <vector>

class Property {
 public:
  Property(const std::string& field_name,
           const std::vector<std::string>& values);

  void addValue(const std::string& value);

  const std::string& getFieldName() const;
  void setFieldName(const std::string& field_name);

  const std::vector<std::string>& getValues() const;
  void setValues(const std::vector<std::string>& values);

 private:
  std::string field_name_;
  std::vector<std::string> values_;
};
