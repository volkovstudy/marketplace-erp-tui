#include "ClientRepository.h"

#include <utility>
#include "../../utils/csvfileservices/csvfileservice/CsvFileService.h"

CsvFileService* fileService;

ClientRepository::ClientRepository(string filePath) {
    fileService = new CsvFileService(std::move(filePath));
}

vector<Client*> ClientRepository::getAll() {
    if (!clients.empty()) return clients;

    vector<Client*> result;
    vector<Property*> allLines = fileService->getAllLines();

    int maxAmountOfLines = 0;
    for (Property* property: allLines) {
        int amountOfLines = (int) property->getValues().size();
        maxAmountOfLines = max(maxAmountOfLines, amountOfLines);
    }

    for (int i = 0; i < maxAmountOfLines; ++i) {
        int id = 0;
        string fullName, email;

        for (Property* property: allLines) {
            if (property->getValues().size() < maxAmountOfLines) break;

            string value = property->getValues().at(i);
            string fieldName = property->getFieldName();

            if (fieldName == "id")
                id = stoi(value);
            if (fieldName == "fullName")
                fullName = value;
            if (fieldName == "email")
                email = value;
        }

        auto* client = new Client(id, fullName, email);
        result.push_back(client);
    }

    clients = result;

    return clients;
}

void write(Client* client) {
    auto* id = new Property("id", {to_string(client->getId())});
    auto* fullName = new Property("fullName", {client->getFullName()});
    auto* email = new Property("email", {client->getEmail()});

    fileService->write({id, fullName, email});
}

void ClientRepository::save(Client* client) {
    clients.push_back(client);

    write(client);
}

Client* ClientRepository::getById(int id) {
    if (clients.empty()) getAll();

    for (Client* client: clients) {
        if (client->getId() == id)
            return client;
    }

    return nullptr;
}
