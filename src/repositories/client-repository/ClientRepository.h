#ifndef MARKETPLACE_ERP_TUI_TESTS_CLIENTREPOSITORY_H
#define MARKETPLACE_ERP_TUI_TESTS_CLIENTREPOSITORY_H


#include <vector>
#include "../../models/client/Client.h"
#include "../../file-services/csv-file-service/CsvFileService.h"

class ClientRepository {
public:
    explicit ClientRepository(string filePath);

    vector<Client*> getAll();
    Client* getById(int id);
    void save(Client* client);
private:
    CsvFileService csvFileService;
    vector<Client*> clients{};
};


#endif
