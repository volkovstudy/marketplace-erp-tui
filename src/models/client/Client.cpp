#include "Client.h"
#include "../../file-services/configuration-service/ConfigurationService.h"

#include <utility>

Client::Client(string fullName, string email) :
        fullName(std::move(fullName)),
        email(std::move(email)) {
    ConfigurationService* configurationService = ConfigurationService::getInstance(
            ConfigurationService::getMainConfigFilePath());

    id = configurationService->getNextId();
    configurationService->save();
}

Client::Client(int id, string fullName, string email) : id(id), fullName(std::move(fullName)),
                                                        email(std::move(email)) {}

int Client::getId() const {
    return id;
}

void Client::setId(int id) {
    Client::id = id;
}

const string& Client::getFullName() const {
    return fullName;
}

void Client::setFullName(const string& fullName) {
    Client::fullName = fullName;
}

const string& Client::getEmail() const {
    return email;
}

void Client::setEmail(const string& email) {
    Client::email = email;
}
