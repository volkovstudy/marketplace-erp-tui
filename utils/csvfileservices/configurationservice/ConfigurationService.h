#ifndef MARKETPLACE_ERP_TUI_CONFIGURATIONSERVICE_H
#define MARKETPLACE_ERP_TUI_CONFIGURATIONSERVICE_H


#include <utility>
#include "../csvfileservice/CsvFileService.h"

class ConfigurationService {
private:
    int currentId = 0;
    CsvFileService *csvFileService;

    explicit ConfigurationService(string filePath);

public:
    static ConfigurationService *getInstance(string filePath);

    static void createInstance(string filePath) {
        instance = new ConfigurationService(std::move(filePath));
    }
};


#endif
