#pragma once

#include <string>
#include <vector>
#include <string_view>

#include "models/Property.h"

class CsvFileService {
 public:
  explicit CsvFileService(std::string_view file_path);

  std::vector<Property> getAllLines() const;

  void write(const std::vector<Property>& properties) const;
  void eraseAndWrite(const std::vector<Property>& properties) const;

  const std::string& getFilePath() const;
  void setFilePath(std::string_view file_path);

 private:
  std::string file_path_;
};
