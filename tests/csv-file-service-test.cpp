#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "file-services/CsvFileService.h"

namespace {

namespace fs = std::filesystem;

class CsvFileServiceTests : public ::testing::Test {
 protected:
  static inline fs::path file_;

  static void SetUpTestSuite() {
    file_ = fs::path(::testing::TempDir()) / "csv-file-service-test.csv";
  }

  static void TearDownTestSuite() {
    std::error_code ec;
    fs::remove_all(file_, ec);
  }
};

std::vector<Property> givenThreeProperties() {
  std::vector<std::string> names;
  names.emplace_back("Tom");
  names.emplace_back("Alex");

  std::vector<std::string> surnames;
  surnames.emplace_back("Petrov");
  surnames.emplace_back("Kotov");
  surnames.emplace_back("Vasiliev");

  std::vector<std::string> ages;
  ages.emplace_back("20");
  ages.emplace_back("30");

  std::vector<Property> properties;
  properties.emplace_back("name", names);
  properties.emplace_back("surname", surnames);
  properties.emplace_back("age", ages);

  return properties;
}

}  // namespace

TEST_F(CsvFileServiceTests, writePropertiesToFile) {
  CsvFileService csvFileService(file_);

  std::vector<Property> properties = givenThreeProperties();

  csvFileService.write(properties);
}
