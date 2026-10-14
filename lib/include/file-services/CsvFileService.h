#pragma once

#include <string>
#include <vector>

#include "models/Property.h"

class CsvFileService {
 public:
  explicit CsvFileService(const std::string& file_path);

  std::vector<Property> getAllLines() const;

  void write(const std::vector<Property>& properties) const;
  void eraseAndWrite(const std::vector<Property>& properties) const;

  const std::string& getFilePath() const;
  void setFilePath(const std::string& file_path);

 private:
  std::string file_path_;
};
