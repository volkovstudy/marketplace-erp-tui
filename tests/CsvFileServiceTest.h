#include "../utils/csvfileservices/csvfileservice/CsvFileService.h"

class CsvFileServiceTest {
private:
    static vector<Property *> givenThreeProperties() {
        vector<string> names;
        names.emplace_back("Tom");
        names.emplace_back("Alex");
        names.emplace_back("Bob");
        auto *name = new Property("name", names);

        vector<string> surnames;
        surnames.emplace_back("Petrov");
        surnames.emplace_back("Kotov");
        surnames.emplace_back("Vasiliev");
        auto *surname = new Property("surname", surnames);

        vector<string> ages;
        ages.emplace_back("20");
        ages.emplace_back("30");
        ages.emplace_back("40");
        auto *age = new Property("age", ages);

        vector<Property *> properties;
        properties.push_back(name);
        properties.push_back(surname);
        properties.push_back(age);

        return properties;
    }

public:
    static void shouldWritePropertiesToFile(string filePath) {
        CsvFileService csvFileService(std::move(filePath));

        vector<Property *> properties = givenThreeProperties();

        csvFileService.write(properties);
    }
};
