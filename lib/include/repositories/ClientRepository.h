#pragma once

#include <optional>
#include <vector>

#include "file-services/CsvFileService.h"
#include "models/Client.h"

class ClientRepository {
 public:
  explicit ClientRepository(CsvFileService& csv_file_service);

  std::vector<Client>& getAll();

  std::optional<Client> getById(int id);

  void save(const Client& client);

 private:
  std::vector<Client> clients_{};

  CsvFileService& csv_file_service_;
};
