#pragma once

#include <vector>

#include "file-services/csv-file-service/CsvFileService.h"
#include "models/client/Client.h"

class ClientRepository {
 public:
  explicit ClientRepository(std::string filePath);

  std::vector<Client*> getAll();
  Client* getById(int id);
  void save(Client* client);

 private:
  CsvFileService csvFileService;
  std::vector<Client*> clients{};
};
