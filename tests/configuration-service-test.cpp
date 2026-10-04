#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "file-services/ConfigurationService.h"

namespace fs = std::filesystem;

static const std::string kTestFilename = "configuration-test.csv";

class ConfigurationServiceTests : public ::testing::Test {
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

TEST_F(ConfigurationServiceTests, getNextId) {
  ConfigurationService* configurationService =
      ConfigurationService::getInstance(file_);

  int actual = configurationService->getNextId();

  ASSERT_EQ(actual, 1);
}

TEST_F(ConfigurationServiceTests, saveNewCurrentId) {
  ConfigurationService* configurationService =
      ConfigurationService::getInstance(file_);

  configurationService->save();

  // Check it. In file should not be 0!
}
