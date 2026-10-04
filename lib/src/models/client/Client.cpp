#include "models/client/Client.h"

#include <string>
#include <utility>

#include "file-services/configuration-service/ConfigurationService.h"

Client::Client(std::string fullName, std::string email)
    : fullName(std::move(fullName)), email(std::move(email)) {
  ConfigurationService* configurationService =
      ConfigurationService::getInstance(
          ConfigurationService::getMainConfigFilePath());

  id = configurationService->getNextId();
  configurationService->save();
}

Client::Client(int id, std::string fullName, std::string email)
    : id(id), fullName(std::move(fullName)), email(std::move(email)) {}

int Client::getId() const { return id; }

void Client::setId(int id) { Client::id = id; }

const std::string& Client::getFullName() const { return fullName; }

void Client::setFullName(const std::string& fullName) {
  Client::fullName = fullName;
}

const std::string& Client::getEmail() const { return email; }

void Client::setEmail(const std::string& email) { Client::email = email; }
