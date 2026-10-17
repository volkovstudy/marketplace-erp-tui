#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#include "models/Property.h"

namespace utils {

void toLowerCase(std::string& line);

void printDelimiter();

size_t FindMaxValuesSize(const std::vector<Property>& properties);

int MapStringToInt(std::string_view str);

const Property& FindColumn(const std::string& column_name,
                           const std::vector<Property>& properties);

}  // namespace utils
