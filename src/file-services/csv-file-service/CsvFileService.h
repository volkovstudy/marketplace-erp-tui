#ifndef MARKETPLACE_ERP_TUI_CSVFILESERVICE_H
#define MARKETPLACE_ERP_TUI_CSVFILESERVICE_H

#include <string>
#include "../../models/property/Property.h"

using namespace std;

class CsvFileService {
public:
    explicit CsvFileService(string filePath);

    vector<Property*> getAllLines();
    void write(vector<Property*> properties);
    void eraseAndWrite(vector<Property*> properties);
    const string& getFilePath() const;
    void setFilePath(const string& newFilePath);
private:
    string filePath;
};


#endif
