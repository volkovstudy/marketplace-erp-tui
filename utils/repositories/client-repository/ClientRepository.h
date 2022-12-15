#ifndef MARKETPLACE_ERP_TUI_TESTS_CLIENTREPOSITORY_H
#define MARKETPLACE_ERP_TUI_TESTS_CLIENTREPOSITORY_H


#include <vector>
#include "../../../public-entities/client/Client.h"

class ClientRepository {
private:
    vector<Client *> clients{};
public:
    explicit ClientRepository(string filePath);

    vector<Client *> getAll();

    void save(Client *client);
};


#endif
