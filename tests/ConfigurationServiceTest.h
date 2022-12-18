#ifndef MARKETPLACE_ERP_TUI_TESTS_CONFIGURATIONSERVICETEST_H
#define MARKETPLACE_ERP_TUI_TESTS_CONFIGURATIONSERVICETEST_H

#include <iostream>
#include <cassert>
#include "../file-services/configuration-service/ConfigurationService.h"

using namespace std;

class ConfigurationServiceTest {
public:
    static void shouldReturnOne(const string& filePath) {
        cout << "Getting next id by from " << filePath << endl;

        ConfigurationService* configurationService = ConfigurationService::getInstance(filePath);
        int expected = configurationService->getNextId();

        assert(1 == expected);
    }

    static void shouldSaveNewCurrentId(const string& filePath) {
        cout << "Saving new current id and getting next id from " << filePath << " ";

        ConfigurationService* configurationService = ConfigurationService::getInstance(filePath);
        configurationService->save();

        cout << "<<< Check it. In file should not be 0!" << endl;
    }
};

#endif
