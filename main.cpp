#include <dirent.h>

#include "src/file-services/configuration-service/ConfigurationService.h"
#include "src/program-launcher/ProgramLauncher.h"

static const std::string mainDirectory = "marketplace-erp";

void createDirectoryIfDoesNotExist(const std::string& name);

int main() {
  createDirectoryIfDoesNotExist(mainDirectory);

  std::string configFilePath = mainDirectory + "/config.csv";
  ConfigurationService::setMainConfigFilePath(configFilePath);

  ProgramLauncher::start();

  return 0;
}

void createDirectoryIfDoesNotExist(const std::string& name) {
  DIR* dir = opendir(name.c_str());

  const std::string command = "mkdir " + name;

  if (!dir) {
    ::system(command.c_str());
  }
}
