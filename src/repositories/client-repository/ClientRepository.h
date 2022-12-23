#ifndef MARKETPLACE_ERP_TUI_TESTS_CLIENTREPOSITORY_H
#define MARKETPLACE_ERP_TUI_TESTS_CLIENTREPOSITORY_H


#include <vector>
#include "../../models/client/Client.h"

class ClientRepository {
public:
    explicit ClientRepository(string filePath);

    vector<Client*> getAll();
    Client* getById(int id);
    void save(Client* client);
private:
    vector<Client*> clients{};
};


#endif
