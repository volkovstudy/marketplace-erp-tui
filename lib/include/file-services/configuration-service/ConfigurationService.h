#pragma once

#include <utility>

#include "file-services/csv-file-service/CsvFileService.h"

class ConfigurationService {
 public:
  static ConfigurationService* getInstance(string filePath);
  static string getMainConfigFilePath();
  static void setMainConfigFilePath(string newFilePath);

  int getNextId();
  void save();

  virtual ~ConfigurationService();

 private:
  explicit ConfigurationService(string filePath);

  int currentId = 0;
  CsvFileService* csvFileService;
};
