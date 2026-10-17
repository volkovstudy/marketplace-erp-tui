#include "repositories/ClientRepository.h"

#include <format>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>

#include "models/Client.h"
#include "models/Property.h"
#include "utils/Utils.h"

namespace {

const Property& FindColumn(const std::string& column_name,
                           const std::vector<Property>& properties) {
  const auto it =
      std::ranges::find(properties, column_name, &Property::getFieldName);

  if (it == properties.end()) {
    throw std::invalid_argument(
        std::format("Column {} isn't found", column_name));
  }

  return *it;
}

void Write(const Client& client, const CsvFileService& csv_file_service) {
  Property id("id", {std::to_string(client.getId())});
  Property fullName("fullName", {client.getFullName()});
  Property email("email", {client.getEmail()});

  csv_file_service.write({id, fullName, email});
}

std::vector<Client> ReadClients(const CsvFileService& csv_file_service) {
  const std::vector<Property> data = csv_file_service.getAllLines();

  const auto& ids = FindColumn("id", data).getValues();
  const auto& names = FindColumn("fullName", data).getValues();
  const auto& emails = FindColumn("email", data).getValues();

  return std::views::zip(ids, names, emails) |
         std::views::transform([](const auto& row) {
           auto [id, name, email] = row;
           return Client{utils::MapStringToInt(id), name, email};
         }) |
         std::ranges::to<std::vector>();
}

}  // namespace

ClientRepository::ClientRepository(CsvFileService& csv_file_service)
    : csv_file_service_(csv_file_service) {}

std::vector<Client>& ClientRepository::getAll() {
  if (clients_.empty()) {
    clients_ = ReadClients(csv_file_service_);
  }

  return clients_;
}

std::optional<Client> ClientRepository::getById(int id) {
  if (clients_.empty()) getAll();

  const auto it = std::ranges::find(clients_, id, &Client::getId);

  return it == clients_.end() ? std::nullopt : std::optional{*it};
}

void ClientRepository::save(const Client& client) {
  clients_.push_back(client);

  Write(client, csv_file_service_);
}
