#include "CsvFileService.h"

#include <utility>
#include <fstream>
#include <vector>

#define CSV_DELIMITER ","
#define LINE_BREAKER "\n"
#define EMPTY_VALUE ""

using namespace std;

CsvFileService::CsvFileService(string filePath) : filePath(std::move(filePath)) {}

const string &CsvFileService::getFilePath() const {
    return filePath;
}

void CsvFileService::setFilePath(const string &newFilePath) {
    CsvFileService::filePath = newFilePath;
}

vector<string> splitLine(const string &str, const string &delimiter) {
    vector<string> result;

    string::size_type currentPosition = str.find(delimiter);;
    string::size_type previousElementIndex = 0;

    while (currentPosition != string::npos) {
        string delimitedLine = str.substr(previousElementIndex, currentPosition - previousElementIndex);
        result.push_back(delimitedLine);

        previousElementIndex = currentPosition + delimiter.size();
        currentPosition = str.find(delimiter, previousElementIndex);
    }

    string lastDelimitedLine = str.substr(previousElementIndex);
    result.push_back(lastDelimitedLine);

    return result;
}

vector<Property *> createVectorWithProperties(const vector<string>& fieldNames) {
    vector<Property *> result;

    for (const auto &fieldName: fieldNames) {
        auto *property = new Property(fieldName, {});

        result.push_back(property);
    }

    return result;
}

vector<string> getColumnNamesFromString(const string &filePath) {
    ifstream fileReader(filePath);

    if (!fileReader.is_open()) return *(new vector<string>);

    string firstLine;
    getline(fileReader, firstLine);

    if (firstLine.empty()) return {};

    return splitLine(firstLine, CSV_DELIMITER);
}

vector<string> getColumnNamesFromProperties(const vector<Property *>& properties) {
    vector<string> columnNames;

    for (Property *property : properties)
        columnNames.push_back(property->getFieldName());

    return columnNames;
}

vector<Property *> CsvFileService::getAllLines() {
    ifstream fileReader(filePath);

    string lineWithColumnNames;
    getline(fileReader, lineWithColumnNames);

    vector<string> fieldNames = splitLine(lineWithColumnNames, CSV_DELIMITER);
    vector<Property *> allLines = createVectorWithProperties(fieldNames);

    string line;
    while (getline(fileReader, line)) {
        vector<string> lineValues = splitLine(line, CSV_DELIMITER);

        for (int i = 0; i < allLines.size(); ++i) {
            Property *property = allLines.at(i);

            vector<string> values = property->getValues();
            values.push_back(lineValues.at(i));

            property->setValues(values);
        }
    }

    fileReader.close();

    return allLines;
}

vector<string> writeColumnNamesToFile(ofstream &fileWriter, vector<string> columnNames) {
    for (int i = 0; i < columnNames.size(); ++i) {
        string columnName = columnNames.at(i);

        fileWriter << columnName;
        bool hasNext = i + 1 < columnNames.size();
        if (hasNext) {
            fileWriter << CSV_DELIMITER;
        } else {
            fileWriter << LINE_BREAKER;
        }
    }
}

void CsvFileService::write(vector<Property *> properties) {
    ofstream fileWriter(filePath, ios::app);

    if (!fileWriter.is_open()) return;

    vector<string> columnNames = getColumnNamesFromString(filePath);

    if (columnNames.empty()) {
        columnNames = getColumnNamesFromProperties(properties);
        writeColumnNamesToFile(fileWriter, columnNames);
    }

    // Sorting properties by their order in file
    vector<Property *> sortedProperties;
    for (Property *property: properties) {
        for (const string &columnName: columnNames) {
            if (property->getFieldName() == columnName)
                sortedProperties.push_back(property);
        }
    }

    // Finding maximal amount of values (lines) in properties
    int maxAmountOfValues = (int) properties.at(0)->getValues().size();
    for (Property *property: properties) {
        int amountOfValues = (int) property->getValues().size();
        maxAmountOfValues = max(maxAmountOfValues, amountOfValues);
    }

    for (int lineNumber = 0; lineNumber < maxAmountOfValues; ++lineNumber) {
        for (int i = 0; i < sortedProperties.size(); ++i) {
            Property *property = sortedProperties.at(i);

            vector<string> values = property->getValues();
            if (lineNumber < values.size())
                fileWriter << property->getValues().at(lineNumber);
            else
                fileWriter << EMPTY_VALUE;

            if (i + 1 < sortedProperties.size()) fileWriter << CSV_DELIMITER;
        }

        fileWriter << LINE_BREAKER;
    }
}
