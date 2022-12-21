#include "ProgramLauncher.h"
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

void toLowerCase(string* line);

void toLowerCase(string* line) {
    transform(line->begin(), line->end(), line->begin(),
              [](unsigned char c) { return tolower(c); }
    );
}
