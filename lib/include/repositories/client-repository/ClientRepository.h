#pragma once

#include <vector>

#include "file-services/csv-file-service/CsvFileService.h"
#include "models/client/Client.h"

class ClientRepository {
 public:
  explicit ClientRepository(string filePath);

  vector<Client*> getAll();
  Client* getById(int id);
  void save(Client* client);

 private:
  CsvFileService csvFileService;
  vector<Client*> clients{};
};
