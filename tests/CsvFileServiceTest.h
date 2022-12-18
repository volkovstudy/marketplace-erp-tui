#include <iostream>
#include "../file-services/csv-file-service/CsvFileService.h"

using namespace std;

class CsvFileServiceTest {
private:
    static vector<Property*> givenThreeProperties() {
        vector<string> names;
        names.emplace_back("Tom");
        names.emplace_back("Alex");
        auto* name = new Property("name", names);

        vector<string> surnames;
        surnames.emplace_back("Petrov");
        surnames.emplace_back("Kotov");
        surnames.emplace_back("Vasiliev");
        auto* surname = new Property("surname", surnames);

        vector<string> ages;
        ages.emplace_back("20");
        ages.emplace_back("30");
        auto* age = new Property("age", ages);

        vector<Property*> properties;
        properties.push_back(name);
        properties.push_back(surname);
        properties.push_back(age);

        return properties;
    }

public:
    static void shouldWritePropertiesToFile(string filePath) {
        cout << "Writing properties to " << filePath << endl;

        CsvFileService csvFileService(std::move(filePath));

        vector<Property*> properties = givenThreeProperties();

        csvFileService.write(properties);
    }
};
