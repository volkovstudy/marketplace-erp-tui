#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include "file-services/configuration-service/ConfigurationService.h"

class ConfigurationServiceTest {
 public:
  static void shouldReturnOne(const std::string& filePath) {
    std::cout << "Getting next id by from " << filePath << std::endl;

    ConfigurationService* configurationService =
        ConfigurationService::getInstance(filePath);
    int expected = configurationService->getNextId();

    assert(1 == expected);
  }

  static void shouldSaveNewCurrentId(const std::string& filePath) {
    std::cout << "Saving new current id and getting next id from " << filePath
              << " ";

    ConfigurationService* configurationService =
        ConfigurationService::getInstance(filePath);
    configurationService->save();

    std::cout << "<<< Check it. In file should not be 0!" << std::endl;
  }
};
