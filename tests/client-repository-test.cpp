#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "file-services/ConfigurationService.h"
#include "file-services/CsvFileService.h"
#include "repositories/ClientRepository.h"

namespace fs = std::filesystem;

static const std::string kClientsFile = "clients-test.csv";
static const std::string kConfigFile = "config-test.csv";

class ClientRepositoryTests : public ::testing::Test {
 protected:
  static inline fs::path dir_;
  static inline fs::path config_file_;
  static inline fs::path clients_file_;

  static void SetUpTestSuite() {
    dir_ = fs::path(::testing::TempDir()) / "marketplace_erp_tui_tests";

    std::error_code ec;
    fs::create_directories(dir_, ec);
    ASSERT_FALSE(ec) << "Cannot create " << dir_ << ": " << ec.message();

    clients_file_ = dir_ / kClientsFile;
    config_file_ = dir_ / kConfigFile;
  }

  static void TearDownTestSuite() {
    std::error_code ec;
    fs::remove_all(dir_, ec);
  }
};

TEST_F(ClientRepositoryTests, saveAndWriteClientToFile) {
  CsvFileService config_csv{config_file_};
  ConfigurationService config_service{config_csv};

  CsvFileService clients_csv{clients_file_};
  ClientRepository clientRepository{clients_csv, config_service};

  Client client(1, "test client", "test.client@example.com");

  clientRepository.save(client);
}

TEST_F(ClientRepositoryTests, getAllClientsFromFile) {
  CsvFileService config_csv{config_file_};
  ConfigurationService config_service{config_csv};

  CsvFileService clients_csv{clients_file_};
  ClientRepository clientRepository{clients_csv, config_service};

  const std::vector<Client>& suppliers = clientRepository.getAll();

  ASSERT_FALSE(suppliers.empty());
}

TEST_F(ClientRepositoryTests, getClientById) {
  CsvFileService config_csv{config_file_};
  ConfigurationService config_service{config_csv};

  CsvFileService clients_csv{clients_file_};
  ClientRepository clientRepository{clients_csv, config_service};

  std::optional<Client> client = clientRepository.getById(1);

  ASSERT_TRUE(client.has_value());
}
