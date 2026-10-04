#pragma once

#include <string>
#include <utility>

#include "file-services/CsvFileService.h"

class ConfigurationService {
 public:
  static ConfigurationService* getInstance(std::string filePath);
  static std::string getMainConfigFilePath();
  static void setMainConfigFilePath(std::string newFilePath);

  int getNextId();
  void save();

  virtual ~ConfigurationService();

 private:
  explicit ConfigurationService(std::string filePath);

  int currentId = 0;
  CsvFileService* csvFileService;
};
