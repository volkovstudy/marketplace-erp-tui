#pragma once

#include "file-services/CsvFileService.h"

class ConfigurationService {
 public:
  explicit ConfigurationService(CsvFileService& csv_file_service);

  ~ConfigurationService();

  int getNextId();
  void save();

 private:
  CsvFileService csv_file_service_;

  int current_id_ = 0;
};
