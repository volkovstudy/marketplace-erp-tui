#pragma once

#include <string>
#include <vector>

class Property {
 public:
  Property(std::string fieldName, const std::vector<std::string>& values);

  const std::string& getFieldName() const;
  void setFieldName(const std::string& fieldName);

  const std::vector<std::string>& getValues() const;
  void setValues(const std::vector<std::string>& values);

 private:
  std::string fieldName;
  std::vector<std::string> values;
};
