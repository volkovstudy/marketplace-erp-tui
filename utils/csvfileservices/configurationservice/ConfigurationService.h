#ifndef MARKETPLACE_ERP_TUI_CONFIGURATIONSERVICE_H
#define MARKETPLACE_ERP_TUI_CONFIGURATIONSERVICE_H


#include "../csvfileservice/CsvFileService.h"

class ConfigurationService {
private:
    static ConfigurationService *instance;

    int nextId;
    CsvFileService *csvFileService;

    explicit ConfigurationService(string filePath);

public:
    static ConfigurationService *getInstance();

    static void createInstance(string filePath);
};


#endif
