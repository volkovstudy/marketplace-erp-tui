#include "ConfigurationService.h"

#include <utility>

ConfigurationService *instance;

ConfigurationService::ConfigurationService(string filePath) {
    csvFileService = new CsvFileService(std::move(filePath));

    for (Property *property: csvFileService->getAllLines()) {
        if (property->getFieldName() == "current_id") {
            currentId = stoi(property->getValues().at(0));
            break;
        }
    }
}

ConfigurationService *ConfigurationService::getInstance(string filePath) {
    if (instance == nullptr)
        instance = new ConfigurationService(std::move(filePath));
    return instance;
}

int ConfigurationService::getNextId() {
    int nextId = currentId + 1;
    currentId = nextId;

    return nextId;
}
