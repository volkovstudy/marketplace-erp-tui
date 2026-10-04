#pragma once

#include <string>
#include <utility>

#include "file-services/CsvFileService.h"

class ConfigurationService {
 public:
  static ConfigurationService* getInstance(const std::string& filePath);
  static std::string getMainConfigFilePath();
  static void setMainConfigFilePath(const std::string& newFilePath);

  ~ConfigurationService();

  int getNextId();
  void save();

 private:
  explicit ConfigurationService(const std::string& filePath);

  int currentId = 0;
  CsvFileService csvFileService;
};
