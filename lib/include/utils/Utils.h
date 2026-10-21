#pragma once

#include <cstddef>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "models/Property.h"

namespace utils {

void toLowerCase(std::string& line);

constexpr char ToLowerCase(char c) {
  return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
}

constexpr char ToUpperCase(char c) {
  return (c >= 'a' && c <= 'z') ? static_cast<char>(c - 'a' + 'A') : c;
}

void PrintDelimiter(std::ostream& out);

size_t FindMaxValuesSize(const std::vector<Property>& properties);

int MapStringToInt(std::string_view str);

const Property& FindColumn(const std::string& column_name,
                           const std::vector<Property>& properties);

}  // namespace utils
