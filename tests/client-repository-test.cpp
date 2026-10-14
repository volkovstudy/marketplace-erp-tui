#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "file-services/CsvFileService.h"
#include "repositories/ClientRepository.h"

namespace fs = std::filesystem;

static const std::string kTestFilename = "clients-test.csv";

class ClientRepositoryTests : public ::testing::Test {
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

TEST_F(ClientRepositoryTests, saveAndWriteClientToFile) {
  CsvFileService clients_csv{file_};
  ClientRepository clientRepository(clients_csv);

  Client client(1, "test client", "test.client@example.com");

  clientRepository.save(client);
}

TEST_F(ClientRepositoryTests, getAllClientsFromFile) {
  CsvFileService clients_csv{file_};
  ClientRepository clientRepository(clients_csv);

  const std::vector<Client>& suppliers = clientRepository.getAll();

  ASSERT_FALSE(suppliers.empty());
}

TEST_F(ClientRepositoryTests, getClientById) {
  CsvFileService clients_csv{file_};
  ClientRepository clientRepository(clients_csv);

  std::optional<Client> client = clientRepository.getById(1);

  ASSERT_TRUE(client.has_value());
}
