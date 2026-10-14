#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "models/Property.h"

namespace utils {

void toLowerCase(std::string& line);

void printDelimiter();

size_t FindMaxValuesSize(const std::vector<Property>& properties);

}  // namespace utils
