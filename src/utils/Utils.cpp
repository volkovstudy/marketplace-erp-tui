#include "Utils.h"

#include <algorithm>

void Utils::toLowerCase(string* line) {
    transform(line->begin(), line->end(), line->begin(),
              [](unsigned char c) { return tolower(c); }
    );
}
