#include "file-services/CsvFileService.h"

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <functional>
#include <ios>
#include <istream>
#include <ostream>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "models/Property.h"

static const std::string kCsvDelimiter = ",";
static const std::string kLineBreaker = "\n";
static const std::string kEmptyValue = "";

namespace {

std::vector<std::string> SplitLine(std::string_view str,
                                   std::string_view delimiter) {
  return std::views::split(str, delimiter) |
         std::views::transform([](const auto& sub) {
           return std::string{sub.begin(), sub.end()};
         }) |
         std::ranges::to<std::vector>();
}

std::vector<std::string> ReadColumnNames(const std::string& file_path) {
  std::ifstream reader(file_path);

  if (!reader.is_open()) return {};

  std::string header;
  std::getline(reader, header);

  if (header.empty()) return {};

  return SplitLine(header, kCsvDelimiter);
}

std::vector<std::string> GetColumnNamesFromProps(
    const std::vector<Property>& properties) {
  return properties | std::views::transform(&Property::getFieldName) |
         std::ranges::to<std::vector>();
}

std::vector<Property> CreateVectorWithProps(
    const std::vector<std::string>& field_names) {
  return field_names |
         std::views::transform([](auto& name) { return Property{name, {}}; }) |
         std::ranges::to<std::vector>();
}

void WriteColumnNames(std::ostream& out,
                      const std::vector<std::string>& column_names) {
  bool is_first = true;

  for (auto& column_name : column_names) {
    if (!is_first) {
      out << kCsvDelimiter;
    }

    out << column_name;
    is_first = false;
  }

  out << kLineBreaker;
}

std::vector<std::reference_wrapper<const Property>> GetOrderedProps(
    const std::vector<Property>& properties,
    const std::vector<std::string>& column_names) {
  std::unordered_map<std::string_view, size_t> order;
  order.reserve(column_names.size());
  for (auto [idx, column_name] : std::views::enumerate(column_names)) {
    order.try_emplace(column_name, static_cast<size_t>(idx));
  }

  std::vector<const Property*> slots(column_names.size(), nullptr);
  for (const auto& prop : properties) {
    if (auto it = order.find(prop.getFieldName()); it != order.end()) {
      slots[it->second] = &prop;
    }
  }

  return slots |
         std::views::filter([](const Property* p) { return p != nullptr; }) |
         std::views::transform(
             [](const Property* p) { return std::cref(*p); }) |
         std::ranges::to<std::vector>();
}

size_t FindMaxValuesSize(const std::vector<Property>& properties) {
  if (properties.empty()) return 0;

  const auto& sizes = properties | std::views::transform([](const Property& p) {
                        return p.getValues().size();
                      });

  return std::ranges::max(sizes);
}

void WriteValues(std::ostream& out, const auto& ordered_props, size_t rows) {
  const auto cell = [](const Property& prop, size_t row) {
    const auto& values = prop.getValues();
    return row < values.size() ? std::string_view{values[row]}
                               : std::string_view{kEmptyValue};
  };

  for (size_t row = 0; row < rows; ++row) {
    for (auto [column, prop] : std::views::enumerate(ordered_props)) {
      if (column != 0) out << kCsvDelimiter;
      out << cell(prop, row);
    }

    out << kLineBreaker;
  }
}

void WriteInSpecificMode(const std::string& file_path,
                         std::ios_base::openmode mode,
                         const std::vector<Property>& properties) {
  std::ofstream writer(file_path, mode);

  if (!writer.is_open()) return;

  std::vector<std::string> column_names = ReadColumnNames(file_path);

  if (column_names.empty()) {
    column_names = GetColumnNamesFromProps(properties);
    WriteColumnNames(writer, column_names);
  }

  const auto ordered_props = GetOrderedProps(properties, column_names);
  const size_t rows = FindMaxValuesSize(properties);

  WriteValues(writer, ordered_props, rows);
}

std::vector<Property> ReadAll(std::istream& in,
                              const std::vector<std::string>& column_names) {
  std::vector<Property> properties = CreateVectorWithProps(column_names);

  for (std::string line; std::getline(in, line);) {
    std::vector<std::string> values = SplitLine(line, kCsvDelimiter);

    for (auto&& [property, value] : std::views::zip(properties, values)) {
      property.addValue(value);
    }
  }

  return properties;
}

}  // namespace

CsvFileService::CsvFileService(const std::string& file_path)
    : file_path_(file_path) {}

std::vector<Property> CsvFileService::getAllLines() const {
  std::ifstream reader(file_path_);

  std::string header;
  std::getline(reader, header);

  std::vector<std::string> column_names = SplitLine(header, kCsvDelimiter);

  return ReadAll(reader, column_names);
}

void CsvFileService::write(const std::vector<Property>& properties) const {
  WriteInSpecificMode(file_path_, std::ios::app, properties);
}

void CsvFileService::eraseAndWrite(
    const std::vector<Property>& properties) const {
  WriteInSpecificMode(file_path_, std::ios::ate, properties);
}

const std::string& CsvFileService::getFilePath() const { return file_path_; }

void CsvFileService::setFilePath(const std::string& file_path) {
  file_path_ = file_path;
}
