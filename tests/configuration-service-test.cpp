#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "file-services/ConfigurationService.h"

namespace {

namespace fs = std::filesystem;

class ConfigurationServiceTests : public ::testing::Test {
 protected:
  static inline std::string file_;

  static void SetUpTestSuite() {
    file_ = fs::path(::testing::TempDir()) / "configuration-test.csv";
  }

  static void TearDownTestSuite() {
    std::error_code ec;
    fs::remove_all(file_, ec);
  }
};

}  // namespace

TEST_F(ConfigurationServiceTests, getNextId) {
  CsvFileService config_csv{file_};
  ConfigurationService configurationService{config_csv};

  int actual = configurationService.getNextId();

  ASSERT_EQ(actual, 1);
}

TEST_F(ConfigurationServiceTests, saveNewCurrentId) {
  CsvFileService config_csv{file_};
  ConfigurationService configurationService{config_csv};

  configurationService.save();

  // Check it. In file should not be 0!
}
