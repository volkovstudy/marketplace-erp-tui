#ifndef MARKETPLACE_ERP_TUI_CONFIGURATIONSERVICE_H
#define MARKETPLACE_ERP_TUI_CONFIGURATIONSERVICE_H


#include <utility>
#include "../csv-file-service/CsvFileService.h"

class ConfigurationService {
private:
    int currentId = 0;
    CsvFileService* csvFileService;

    explicit ConfigurationService(string filePath);
public:
    static ConfigurationService* getInstance(string filePath);
    static string getMainConfigFilePath();
    static void setMainConfigFilePath(string newFilePath);

    int getNextId();
    void save();

    virtual ~ConfigurationService();
};


#endif
