#include "models/Property.h"

#include <string>
#include <vector>

Property::Property(const std::string& field_name,
                   const std::vector<std::string>& values)
    : field_name_(field_name), values_(values) {}

void Property::addValue(const std::string& value) { values_.push_back(value); }

const std::string& Property::getFieldName() const { return field_name_; }

void Property::setFieldName(const std::string& field_name) {
  field_name_ = field_name;
}

const std::vector<std::string>& Property::getValues() const { return values_; }

void Property::setValues(const std::vector<std::string>& values) {
  values_ = values;
}
