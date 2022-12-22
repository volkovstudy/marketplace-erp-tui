#include <dirent.h>
#include "src/program-launcher/ProgramLauncher.h"
#include "src/file-services/configuration-service/ConfigurationService.h"

#define mainDirectory "marketplace-erp"

using namespace std;

void createDirectoryIfDoesNotExist(const string& name);

int main() {
    createDirectoryIfDoesNotExist(mainDirectory);

    string configFilePath = mainDirectory"/config.csv";
    ConfigurationService::setMainConfigFilePath(configFilePath);

    ProgramLauncher::start();

    return 0;
}

void createDirectoryIfDoesNotExist(const string& name) {
    DIR* dir = opendir(name.c_str());

    string command = "mkdir ";
    command += name;

    if (!dir) {
        ::system(command.c_str());
    }
}
