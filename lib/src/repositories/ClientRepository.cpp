#include "repositories/ClientRepository.h"

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "models/Client.h"
#include "models/Property.h"

namespace {

void write(const Client& client, CsvFileService& csv_file_service) {
  auto* id = new Property("id", {std::to_string(client.getId())});
  auto* fullName = new Property("fullName", {client.getFullName()});
  auto* email = new Property("email", {client.getEmail()});

  csv_file_service.write({id, fullName, email});
}

}  // namespace

ClientRepository::ClientRepository(CsvFileService& csv_file_service)
    : csv_file_service_(csv_file_service) {}

std::vector<Client>& ClientRepository::getAll() {
  if (!clients_.empty()) return clients_;

  std::vector<Client> result;
  std::vector<Property*> allLines = csv_file_service_.getAllLines();

  int maxAmountOfLines = 0;
  for (Property* property : allLines) {
    int amountOfLines = (int)property->getValues().size();
    maxAmountOfLines = std::max(maxAmountOfLines, amountOfLines);
  }

  for (int i = 0; i < maxAmountOfLines; ++i) {
    int id = 0;
    std::string fullName, email;

    for (Property* property : allLines) {
      if (property->getValues().size() < maxAmountOfLines) break;

      std::string value = property->getValues().at(i);
      std::string fieldName = property->getFieldName();

      if (fieldName == "id") id = stoi(value);
      if (fieldName == "fullName") fullName = value;
      if (fieldName == "email") email = value;
    }

    result.emplace_back(id, fullName, email);
  }

  clients_ = result;

  return clients_;
}

std::optional<Client> ClientRepository::getById(int id) {
  if (clients_.empty()) getAll();

  for (auto& client : clients_) {
    if (client.getId() == id) return client;
  }

  return std::nullopt;
}

void ClientRepository::save(const Client& client) {
  clients_.push_back(client);

  write(client, csv_file_service_);
}
