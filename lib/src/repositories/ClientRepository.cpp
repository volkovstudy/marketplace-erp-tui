#include "repositories/ClientRepository.h"

#include <optional>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include "file-services/ConfigurationService.h"
#include "models/Client.h"
#include "models/Property.h"
#include "utils/Utils.h"

namespace {

void Write(const Client& client, const CsvFileService& csv_file_service) {
  Property id("id", {std::to_string(client.getId())});
  Property fullName("fullName", {client.getFullName()});
  Property email("email", {client.getEmail()});

  csv_file_service.write({id, fullName, email});
}

std::vector<Client> ReadClients(const CsvFileService& csv_file_service) {
  const std::vector<Property> data = csv_file_service.getAllLines();

  if (data.empty()) return {};

  const auto& ids = utils::FindColumn("id", data).getValues();
  const auto& names = utils::FindColumn("fullName", data).getValues();
  const auto& emails = utils::FindColumn("email", data).getValues();

  return std::views::zip(ids, names, emails) |
         std::views::transform([](const auto& row) {
           auto [id, name, email] = row;
           return Client{utils::MapStringToInt(id), name, email};
         }) |
         std::ranges::to<std::vector>();
}

}  // namespace

ClientRepository::ClientRepository(CsvFileService& csv_file_service,
                                   ConfigurationService& config_service)
    : clients_(ReadClients(csv_file_service)),
      csv_file_service_(csv_file_service),
      config_service_(config_service) {}

std::vector<Client>& ClientRepository::getAll() { return clients_; }

const std::vector<Client>& ClientRepository::getAll() const { return clients_; }

std::optional<Client> ClientRepository::getById(int id) const {
  const auto it = std::ranges::find(clients_, id, &Client::getId);

  return it == clients_.end() ? std::nullopt : std::optional{*it};
}

ClientRepository::ClientId ClientRepository::save(Client client) {
  const ClientId id =
      client.getId() == -1 ? config_service_.getNextId() : client.getId();
  client.setId(id);

  const Client& stored = clients_.emplace_back(std::move(client));

  Write(stored, csv_file_service_);

  return id;
}
