#include "file-services/ConfigurationService.h"

#include <string>
#include <utility>

#include "file-services/CsvFileService.h"
#include "models/Property.h"

namespace {

const std::string kCurrentIdColumn = "current_id";

}  // namespace

ConfigurationService::ConfigurationService(CsvFileService& csv_file_service)
    : csv_file_service_(csv_file_service) {
  for (const Property& property : csv_file_service.getAllLines()) {
    if (property.getFieldName() == kCurrentIdColumn) {
      int element = std::stoi(property.getValues().at(0));
      current_id_ = element;
      break;
    }
  }
}

ConfigurationService::~ConfigurationService() { save(); }

int ConfigurationService::getNextId() {
  int next_id = current_id_ + 1;
  current_id_ = next_id;

  return next_id;
}

void ConfigurationService::save() {
  Property property(kCurrentIdColumn, {std::to_string(current_id_)});

  csv_file_service_.eraseAndWrite({property});
}
