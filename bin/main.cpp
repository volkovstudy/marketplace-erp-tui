#include <dirent.h>

#include <iostream>

#include "file-services/ConfigurationService.h"
#include "program-launcher/ProgramLauncher.h"

static const std::string mainDirectory = "marketplace-erp";

void createDirectoryIfDoesNotExist(const std::string& name);

int main() {
  createDirectoryIfDoesNotExist(mainDirectory);

  std::string configFilePath = mainDirectory + "/config.csv";
  ConfigurationService::setMainConfigFilePath(configFilePath);

  ProgramLauncher launcher(std::cout, std::cin);
  launcher.start();

  return 0;
}

void createDirectoryIfDoesNotExist(const std::string& name) {
  DIR* dir = opendir(name.c_str());

  const std::string command = "mkdir " + name;

  if (!dir) {
    ::system(command.c_str());
  }
}
