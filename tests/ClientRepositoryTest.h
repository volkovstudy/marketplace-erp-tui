#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "repositories/client-repository/ClientRepository.h"

class ClientRepositoryTest {
 public:
  static void shouldWriteClientToFile(std::string filePath) {
    std::cout << "Saving & writing Client to " << filePath << std::endl;

    ClientRepository clientRepository(std::move(filePath));
    auto* client = new Client(1, "test client", "test.client@example.com");

    clientRepository.save(client);
  }

  static void shouldGetAllClientsFromFile(std::string filePath) {
    std::cout << "Getting all clients from " << filePath << std::endl;

    ClientRepository clientRepository(std::move(filePath));

    std::vector<Client*> suppliers = clientRepository.getAll();

    assert(!suppliers.empty());
  }

  static void shouldGetClientByIdOne(std::string filePath) {
    std::cout << "Getting Client by id 1 from " << filePath << std::endl;

    ClientRepository clientRepository(std::move(filePath));

    Client* client = clientRepository.getById(1);

    assert(client != nullptr);
  }
};
