#include "models/property/Property.h"

#include <string>
#include <utility>
#include <vector>

Property::Property(std::string fieldName,
                   const std::vector<std::string>& values)
    : fieldName(std::move(fieldName)), values(values) {}

const std::string& Property::getFieldName() const { return fieldName; }

void Property::setFieldName(const std::string& newFieldName) {
  Property::fieldName = newFieldName;
}

const std::vector<std::string>& Property::getValues() const { return values; }

void Property::setValues(const std::vector<std::string>& newValues) {
  Property::values = newValues;
}
