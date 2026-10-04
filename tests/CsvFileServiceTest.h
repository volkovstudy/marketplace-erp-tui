#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "file-services/csv-file-service/CsvFileService.h"

class CsvFileServiceTest {
 public:
  static void shouldWritePropertiesToFile(std::string filePath) {
    std::cout << "Writing properties to " << filePath << std::endl;

    CsvFileService csvFileService(std::move(filePath));

    std::vector<Property*> properties = givenThreeProperties();

    csvFileService.write(properties);
  }

 private:
  static std::vector<Property*> givenThreeProperties() {
    std::vector<std::string> names;
    names.emplace_back("Tom");
    names.emplace_back("Alex");
    auto* name = new Property("name", names);

    std::vector<std::string> surnames;
    surnames.emplace_back("Petrov");
    surnames.emplace_back("Kotov");
    surnames.emplace_back("Vasiliev");
    auto* surname = new Property("surname", surnames);

    std::vector<std::string> ages;
    ages.emplace_back("20");
    ages.emplace_back("30");
    auto* age = new Property("age", ages);

    std::vector<Property*> properties;
    properties.push_back(name);
    properties.push_back(surname);
    properties.push_back(age);

    return properties;
  }
};
