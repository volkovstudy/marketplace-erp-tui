#include "Utils.h"

#include <iostream>
#include <algorithm>

using namespace std;

void Utils::toLowerCase(string* line) {
    transform(line->begin(), line->end(), line->begin(),
              [](unsigned char c) { return tolower(c); }
    );
}

void Utils::printDelimiter() {
    cout << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << endl;
}
