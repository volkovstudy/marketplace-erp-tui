#ifndef MARKETPLACE_ERP_TUI_TESTS_CLIENTREPOSITORYTEST_H
#define MARKETPLACE_ERP_TUI_TESTS_CLIENTREPOSITORYTEST_H

#include <iostream>
#include <cassert>
#include "../utils/repositories/client-repository/ClientRepository.h"

class ClientRepositoryTest {
public:
    static void shouldWriteClientToFile(string filePath) {
        cout << "Saving & writing Client to " << filePath << endl;

        ClientRepository clientRepository(std::move(filePath));
        auto *client = new Client(1, "test client", "test.client@example.com");

        clientRepository.save(client);
    }

    static void shouldGetAllClientsFromFile(string filePath) {
        cout << "Getting all clients from " << filePath << endl;

        ClientRepository clientRepository(std::move(filePath));

        vector<Client *> suppliers = clientRepository.getAll();

        assert(!suppliers.empty());
    }
};

#endif
