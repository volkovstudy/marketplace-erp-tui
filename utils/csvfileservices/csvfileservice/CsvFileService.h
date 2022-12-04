#ifndef MARKETPLACE_ERP_TUI_CSVFILESERVICE_H
#define MARKETPLACE_ERP_TUI_CSVFILESERVICE_H

#include <string>
#include "../../property/Property.h"

using namespace std;

class CsvFileService {
private:
    string filePath;
public:
    explicit CsvFileService(string filePath);

    vector<Property *> getAllLines();

    void write(vector<Property *> properties);

    const string &getFilePath() const;
    void setFilePath(const string &newFilePath);
};


#endif
