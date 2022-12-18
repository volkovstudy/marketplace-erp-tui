#ifndef MARKETPLACE_ERP_TUI_PROPERTY_H
#define MARKETPLACE_ERP_TUI_PROPERTY_H

#include <string>
#include <vector>

using namespace std;

class Property {
private:
    string fieldName;
    vector<string> values;
public:
    Property(string fieldName, const vector<string>& values);

    const string& getFieldName() const;

    void setFieldName(const string& fieldName);

    const vector<string>& getValues() const;

    void setValues(const vector<string>& values);
};


#endif
