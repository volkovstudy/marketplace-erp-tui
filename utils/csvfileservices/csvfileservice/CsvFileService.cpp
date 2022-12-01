#include "CsvFileService.h"

#include <utility>
#include <fstream>
#include <vector>

#define CSV_DELIMITER ","

using namespace std;

CsvFileService::CsvFileService(string filePath) : filePath(std::move(filePath)) {}

const string &CsvFileService::getFilePath() const {
    return filePath;
}

void CsvFileService::setFilePath(const string &newFilePath) {
    CsvFileService::filePath = newFilePath;
}

vector<string> splitLine(const string& str, const string& delimiter) {
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

vector<Property*> createVectorWithProperties(vector<string> fieldNames) {
    vector<Property*> result;

    for (int i = 0; i < fieldNames.size(); ++i) {
        string fieldName = fieldNames.at(i);
        Property *property = new Property(fieldName, {});

        result.push_back(property);
    }

    return result;
}

vector<string> getColumnNames(const string& filePath) {
    ifstream fileReader(filePath);

    if (!fileReader.is_open()) return *(new vector<string>);

    string firstLine;
    getline(fileReader, firstLine);

    return splitLine(firstLine, CSV_DELIMITER);
}

vector<Property*> CsvFileService::getAllLines() {
    ifstream fileReader(filePath);

    string lineWithColumnNames;
    getline(fileReader, lineWithColumnNames);

    vector<string> fieldNames = splitLine(lineWithColumnNames, CSV_DELIMITER);
    vector<Property*> allLines = createVectorWithProperties(fieldNames);

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
