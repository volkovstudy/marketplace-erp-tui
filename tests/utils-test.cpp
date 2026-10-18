#include "utils/Utils.h"

#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(UtilsTests, PrintedNeededDelimiter) {
  static const std::string expected =
      "\n--------------------------------------------------------\n\n";

  std::ostringstream out;
  utils::PrintDelimiter(out);

  ASSERT_EQ(out.str(), expected);
}
