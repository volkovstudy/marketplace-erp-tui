#include "Property.h"

#include <utility>

Property::Property(string fieldName, const vector<string>& values) :
        fieldName(std::move(fieldName)),
        values(values) {}

const string& Property::getFieldName() const {
    return fieldName;
}

void Property::setFieldName(const string& newFieldName) {
    Property::fieldName = newFieldName;
}

const vector<string>& Property::getValues() const {
    return values;
}

void Property::setValues(const vector<string>& newValues) {
    Property::values = newValues;
}
