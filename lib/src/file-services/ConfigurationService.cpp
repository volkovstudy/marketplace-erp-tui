#include "file-services/ConfigurationService.h"

#include <string>
#include <utility>

namespace {

static const std::string kCurrentIdColumn = "current_id";

static ConfigurationService* instance;
static std::string mainConfiguration;

}  // namespace

ConfigurationService::ConfigurationService(const std::string& filePath)
    : csvFileService(filePath) {
  for (Property* property : csvFileService.getAllLines()) {
    if (property->getFieldName() == kCurrentIdColumn) {
      int element = std::stoi(property->getValues().at(0));
      currentId = element;
      break;
    }
  }
}

ConfigurationService::~ConfigurationService() { instance->save(); }

ConfigurationService* ConfigurationService::getInstance(
    const std::string& filePath) {
  if (instance == nullptr) instance = new ConfigurationService(filePath);

  return instance;
}

std::string ConfigurationService::getMainConfigFilePath() {
  return mainConfiguration;
}

void ConfigurationService::setMainConfigFilePath(
    const std::string& newFilePath) {
  mainConfiguration = newFilePath;
}

int ConfigurationService::getNextId() {
  int nextId = currentId + 1;
  currentId = nextId;

  return nextId;
}

void ConfigurationService::save() {
  auto* property = new Property(kCurrentIdColumn, {std::to_string(currentId)});

  csvFileService.eraseAndWrite({property});
}
