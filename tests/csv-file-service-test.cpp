#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "file-services/csv-file-service/CsvFileService.h"

namespace fs = std::filesystem;

static const std::string kTestFilename = "csv-file-service-test.csv";

class CsvFileServiceTests : public ::testing::Test {
 protected:
  static inline fs::path file_;

  static void SetUpTestSuite() {
    file_ = fs::path(::testing::TempDir()) / kTestFilename;
  }

  static void TearDownTestSuite() {
    std::error_code ec;
    fs::remove_all(file_, ec);
  }
};

namespace {

static std::vector<Property*> givenThreeProperties() {
  std::vector<std::string> names;
  names.emplace_back("Tom");
  names.emplace_back("Alex");
  auto* name = new Property("name", names);

  std::vector<std::string> surnames;
  surnames.emplace_back("Petrov");
  surnames.emplace_back("Kotov");
  surnames.emplace_back("Vasiliev");
  auto* surname = new Property("surname", surnames);

  std::vector<std::string> ages;
  ages.emplace_back("20");
  ages.emplace_back("30");
  auto* age = new Property("age", ages);

  std::vector<Property*> properties;
  properties.push_back(name);
  properties.push_back(surname);
  properties.push_back(age);

  return properties;
}

}  // namespace

TEST_F(CsvFileServiceTests, writePropertiesToFile) {
  CsvFileService csvFileService(file_);

  std::vector<Property*> properties = givenThreeProperties();

  csvFileService.write(properties);
}
