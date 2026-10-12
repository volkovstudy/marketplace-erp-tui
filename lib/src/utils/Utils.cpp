#include "utils/Utils.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace utils {

void toLowerCase(std::string* line) {
  std::transform(line->begin(), line->end(), line->begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

void printDelimiter() {
  std::cout << std::endl;
  std::cout << "--------------------------------------------------------"
            << std::endl;
  std::cout << std::endl;
}

}  // namespace utils