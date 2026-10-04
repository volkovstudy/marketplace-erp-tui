#include "file-services/CsvFileService.h"

#include <algorithm>
#include <fstream>
#include <ios>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#define CSV_DELIMITER ","
#define LINE_BREAKER "\n"
#define EMPTY_VALUE ""

CsvFileService::CsvFileService(std::string filePath)
    : filePath(std::move(filePath)) {}

const std::string& CsvFileService::getFilePath() const { return filePath; }

void CsvFileService::setFilePath(const std::string& newFilePath) {
  CsvFileService::filePath = newFilePath;
}

std::vector<std::string> splitLine(const std::string& str,
                                   const std::string& delimiter) {
  std::vector<std::string> result;

  std::string::size_type currentPosition = str.find(delimiter);

  std::string::size_type previousElementIndex = 0;

  while (currentPosition != std::string::npos) {
    std::string delimitedLine = str.substr(
        previousElementIndex, currentPosition - previousElementIndex);
    result.push_back(delimitedLine);

    previousElementIndex = currentPosition + delimiter.size();
    currentPosition = str.find(delimiter, previousElementIndex);
  }

  std::string lastDelimitedLine = str.substr(previousElementIndex);
  result.push_back(lastDelimitedLine);

  return result;
}

std::vector<Property*> createVectorWithProperties(
    const std::vector<std::string>& fieldNames) {
  std::vector<Property*> result;

  for (const auto& fieldName : fieldNames) {
    auto* property = new Property(fieldName, {});

    result.push_back(property);
  }

  return result;
}

std::vector<std::string> getColumnNamesFromString(const std::string& filePath) {
  std::ifstream fileReader(filePath);

  if (!fileReader.is_open()) return *(new std::vector<std::string>);

  std::string firstLine;
  std::getline(fileReader, firstLine);

  if (firstLine.empty()) return {};

  return splitLine(firstLine, CSV_DELIMITER);
}

std::vector<std::string> getColumnNamesFromProperties(
    const std::vector<Property*>& properties) {
  std::vector<std::string> columnNames;

  for (Property* property : properties)
    columnNames.push_back(property->getFieldName());

  return columnNames;
}

std::vector<Property*> CsvFileService::getAllLines() {
  std::ifstream fileReader(filePath);

  std::string lineWithColumnNames;
  std::getline(fileReader, lineWithColumnNames);

  std::vector<std::string> fieldNames =
      splitLine(lineWithColumnNames, CSV_DELIMITER);
  std::vector<Property*> allLines = createVectorWithProperties(fieldNames);

  std::string line;
  while (std::getline(fileReader, line)) {
    std::vector<std::string> lineValues = splitLine(line, CSV_DELIMITER);

    for (int i = 0; i < allLines.size(); ++i) {
      Property* property = allLines.at(i);

      std::vector<std::string> values = property->getValues();
      values.push_back(lineValues.at(i));

      property->setValues(values);
    }
  }

  fileReader.close();

  return allLines;
}

void writeColumnNamesToFile(std::ofstream& fileWriter,
                            std::vector<std::string> columnNames) {
  for (int i = 0; i < columnNames.size(); ++i) {
    std::string columnName = columnNames.at(i);

    fileWriter << columnName;
    bool hasNext = i + 1 < columnNames.size();
    if (hasNext) {
      fileWriter << CSV_DELIMITER;
    } else {
      fileWriter << LINE_BREAKER;
    }
  }
}

void writeInSpecificMode(const std::string& filePath,
                         std::ios_base::openmode mode,
                         std::vector<Property*> properties) {
  std::ofstream fileWriter(filePath, mode);

  if (!fileWriter.is_open()) return;

  std::vector<std::string> columnNames = getColumnNamesFromString(filePath);

  if (columnNames.empty()) {
    columnNames = getColumnNamesFromProperties(properties);
    writeColumnNamesToFile(fileWriter, columnNames);
  }

  // Sorting properties by their order in file
  std::vector<Property*> sortedProperties;
  for (Property* property : properties) {
    for (const std::string& columnName : columnNames) {
      if (property->getFieldName() == columnName)
        sortedProperties.push_back(property);
    }
  }

  // Finding maximal amount of values (lines) in properties
  int maxAmountOfValues = (int)properties.at(0)->getValues().size();
  for (Property* property : properties) {
    int amountOfValues = (int)property->getValues().size();
    maxAmountOfValues = std::max(maxAmountOfValues, amountOfValues);
  }

  for (int lineNumber = 0; lineNumber < maxAmountOfValues; ++lineNumber) {
    for (int i = 0; i < sortedProperties.size(); ++i) {
      Property* property = sortedProperties.at(i);

      std::vector<std::string> values = property->getValues();
      if (lineNumber < values.size())
        fileWriter << property->getValues().at(lineNumber);
      else
        fileWriter << EMPTY_VALUE;

      if (i + 1 < sortedProperties.size()) fileWriter << CSV_DELIMITER;
    }

    fileWriter << LINE_BREAKER;
  }
}

void CsvFileService::write(std::vector<Property*> properties) {
  writeInSpecificMode(filePath, std::ios::app, std::move(properties));
}

void CsvFileService::eraseAndWrite(std::vector<Property*> properties) {
  writeInSpecificMode(filePath, std::ios::ate, std::move(properties));
}
