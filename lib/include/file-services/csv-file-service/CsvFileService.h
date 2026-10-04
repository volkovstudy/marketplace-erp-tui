#pragma once

#include <string>
#include <vector>

#include "models/property/Property.h"

class CsvFileService {
 public:
  explicit CsvFileService(std::string filePath);

  std::vector<Property*> getAllLines();
  void write(std::vector<Property*> properties);
  void eraseAndWrite(std::vector<Property*> properties);
  const std::string& getFilePath() const;
  void setFilePath(const std::string& newFilePath);

 private:
  std::string filePath;
};
