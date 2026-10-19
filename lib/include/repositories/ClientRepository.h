#pragma once

#include <optional>
#include <vector>

#include "file-services/ConfigurationService.h"
#include "file-services/CsvFileService.h"
#include "models/Client.h"

class ClientRepository {
 public:
  using ClientId = int;

  explicit ClientRepository(CsvFileService& csv_file_service,
                            ConfigurationService& config_service);

  std::vector<Client>& getAll();
  const std::vector<Client>& getAll() const;

  std::optional<Client> getById(int id) const;

  ClientId save(Client client);

 private:
  std::vector<Client> clients_;

  CsvFileService& csv_file_service_;
  ConfigurationService& config_service_;
};
