#include "utils/Utils.h"

#include <algorithm>
#include <charconv>
#include <cstddef>
#include <format>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "models/Property.h"

namespace utils {

void toLowerCase(std::string& line) {
  std::transform(line.begin(), line.end(), line.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

void printDelimiter() {
  std::cout << std::endl;
  std::cout << "--------------------------------------------------------"
            << std::endl;
  std::cout << std::endl;
}

size_t FindMaxValuesSize(const std::vector<Property>& properties) {
  if (properties.empty()) return 0;

  const auto& sizes = properties | std::views::transform([](const Property& p) {
                        return p.getValues().size();
                      });

  return std::ranges::max(sizes);
}

int MapStringToInt(std::string_view str) {
  int result{};

  const char* first = str.data();
  const char* last = first + str.size();

  const auto [ptr, ec] = std::from_chars(first, last, result);
  if (ec != std::errc{} || ptr != last) {
    throw std::invalid_argument(
        std::format("Failed mapping string {} to int", str));
  }

  return result;
}

const Property& FindColumn(const std::string& column_name,
                           const std::vector<Property>& properties) {
  const auto it =
      std::ranges::find(properties, column_name, &Property::getFieldName);

  if (it == properties.end()) {
    throw std::invalid_argument(
        std::format("Column {} isn't found", column_name));
  }

  return *it;
}

}  // namespace utils