#include "utils/Utils.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string>
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

}  // namespace utils