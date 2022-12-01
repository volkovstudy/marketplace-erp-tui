#include "ConfigurationService.h"

#include <utility>

ConfigurationService::ConfigurationService(string filePath)
        : csvFileService(new CsvFileService(std::move(filePath))) {
    for (Property *property: csvFileService->getAllLines()) {
        if (property->getFieldName() == "id") {
            nextId = stoi(property->getValues().at(0));
            break;
        }
    }
}
