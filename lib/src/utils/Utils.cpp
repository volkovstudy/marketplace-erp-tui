#include "utils/Utils.h"

#include <algorithm>
#include <iostream>
#include <string>

void Utils::toLowerCase(std::string* line) {
  std::transform(line->begin(), line->end(), line->begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

void Utils::printDelimiter() {
  std::cout << std::endl;
  std::cout << "--------------------------------------------------------"
            << std::endl;
  std::cout << std::endl;
}
