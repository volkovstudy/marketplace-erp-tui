#include "file-services/configuration-service/ConfigurationService.h"

#include <string>
#include <utility>

#define currentIdColumn "current_id"

std::string mainConfiguration;

ConfigurationService* instance;

ConfigurationService::ConfigurationService(std::string filePath) {
  csvFileService = new CsvFileService(std::move(filePath));

  for (Property* property : csvFileService->getAllLines()) {
    if (property->getFieldName() == currentIdColumn) {
      currentId = stoi(property->getValues().at(0));
      break;
    }
  }
}

ConfigurationService* ConfigurationService::getInstance(std::string filePath) {
  if (instance == nullptr)
    instance = new ConfigurationService(std::move(filePath));
  return instance;
}

int ConfigurationService::getNextId() {
  int nextId = currentId + 1;
  currentId = nextId;

  return nextId;
}

void ConfigurationService::save() {
  auto* property = new Property(currentIdColumn, {std::to_string(currentId)});

  csvFileService->eraseAndWrite({property});
}

std::string ConfigurationService::getMainConfigFilePath() {
  return mainConfiguration;
}

void ConfigurationService::setMainConfigFilePath(std::string newFilePath) {
  mainConfiguration = std::move(newFilePath);
}

ConfigurationService::~ConfigurationService() { instance->save(); }
