#include "table-printer/TablePrinter.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <ostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

namespace {

constexpr size_t kIndentLength = 10;

constexpr char kLineEnd = '\n';

void PrintHorizontalLine(std::ostream& out, size_t length) {
  out << std::string(length, '-') << kLineEnd;
}

void PrintTableName(std::ostream& out, const std::string& table_name,
                    size_t line_length) {
  size_t indent_length = line_length / 2;

  bool is_length_odd = line_length % 2 != 0;
  if (is_length_odd) indent_length++;

  out << '|';
  out.width(indent_length);
  out << table_name;

  if (is_length_odd) {  // -1 / -2 => because begins printing after all width
    out.width(indent_length - 2);
  } else {
    out.width(indent_length - 1);
  }

  out << '|' << kLineEnd;
}

void PrintHeader(std::ostream& out, size_t line_length,
                 const std::string& table_name) {
  PrintHorizontalLine(out, line_length);
  PrintTableName(out, table_name, line_length);
  PrintHorizontalLine(out, line_length);
}

std::string makeClientLine(const Client& client) {
  std::stringstream clientLine;
  clientLine << client.getFullName() << " <" << client.getEmail() << ">";
  return clientLine.str();
}

std::string makeProductLine(const Product& product) {
  int amount = product.getAmount();

  std::stringstream productLine;
  productLine << product.getName() << " - " << amount;

  if (amount == 1) {
    productLine << " unit";
  } else {
    productLine << " units";
  }

  return productLine.str();
}

}  // namespace

TablePrinter::TablePrinter(std::ostream& out) : out_(out) {}

void TablePrinter::printVector(const std::vector<Client>& clients) {
  const size_t max_name_length =
      std::ranges::max(clients | std::views::transform([](const auto& c) {
                         return c.getFullName().length();
                       }));

  const size_t max_email_length =
      std::ranges::max(clients | std::views::transform([](const auto& c) {
                         return c.getEmail().length();
                       }));

  // indentLength * 2 => because of left & right indent
  // + 3 => because of three '|' characters in header
  const size_t line_length =
      max_name_length + max_email_length + (kIndentLength * 2) + 3;
  PrintHeader(out_, line_length, "*Clients*");

  out_ << '|';
  out_.width(max_name_length + kIndentLength);
  out_ << "NAME " << " |";

  // -2 => because of two spaces in next line
  out_.width(max_email_length + kIndentLength - 2);
  out_ << "EMAIL " << " |" << kLineEnd;

  PrintHorizontalLine(out_, line_length);

  for (const auto& client : clients) {
    out_ << "| ";
    out_.width(max_name_length + kIndentLength - 1);
    out_ << std::right << client.getFullName() << " |";

    // -2 => because of one space in " |" in NAME column &  one space in the end
    out_.width(max_email_length + kIndentLength - 2);
    out_ << std::right << client.getEmail() << " |" << kLineEnd;
  }

  PrintHorizontalLine(out_, line_length);
}

void TablePrinter::printVector(const std::vector<Order>& orders) {
  std::map<const Order*, std::string> idStrings;
  std::map<const Order*, std::string> clientLines;
  std::map<const Order*, std::vector<std::string>> productLines;

  int maxLengthOfId = 0, maxLengthOfClientLine = 0, maxLengthOfProductLine = 0;
  for (auto& order : orders) {
    std::string idString = std::to_string(order.getId());
    idStrings[&order] = idString;
    int idLength = (int)idString.length();
    maxLengthOfId = std::max(maxLengthOfId, idLength);

    Client client = order.getClient();
    std::string clientLine = makeClientLine(client);
    clientLines[&order] = clientLine;
    maxLengthOfClientLine =
        std::max(maxLengthOfClientLine, (int)clientLine.length());

    std::vector<std::string> productsLines;
    for (auto& product : order.getProducts()) {
      std::string productLine = makeProductLine(product);
      maxLengthOfProductLine =
          std::max(maxLengthOfProductLine, (int)productLine.length());

      productsLines.push_back(productLine);
    }
    productLines[&order] = productsLines;
  }

  // indentLength * 2 => because of left & right indent
  // + 4 => because of four '|' characters in header
  // + 4 => because of spaces before '|' characters in header
  int lineLength = maxLengthOfId + maxLengthOfClientLine +
                   maxLengthOfProductLine + (kIndentLength * 2) + 4 + 4;
  PrintHeader(out_, lineLength, "*Orders*");

  std::cout << "|";
  std::cout.width(maxLengthOfId + kIndentLength);
  std::cout << "ID " << " |";

  std::cout.width(maxLengthOfClientLine +
                  1);  // +1 => because of 1 space in " |"
  std::cout << "CLIENT " << " |";

  std::cout.width(maxLengthOfProductLine + kIndentLength);
  std::cout << "PRODUCTS " << " |";
  std::cout << std::endl;

  PrintHorizontalLine(out_, lineLength);

  int widthForId = maxLengthOfId + kIndentLength;
  // +1 => because we need a space after previous '|' in ID column AND because
  // we don't have indent there
  int widthForClient = maxLengthOfClientLine + 1;
  int widthForProducts = maxLengthOfProductLine + kIndentLength;

  for (auto& order : orders) {
    std::cout << "|";

    std::cout.width(widthForId);
    std::cout << std::right << idStrings[&order] << " |";

    std::cout.width(widthForClient);
    std::cout << std::right << clientLines[&order] << " |";

    std::vector<std::string> productsLines = productLines[&order];
    std::cout.width(widthForProducts);
    std::cout << std::right
              << (productsLines.empty() ? "" : productsLines.at(0)) << " |"
              << std::endl;

    // Starts from 1 because we've already printed the first line
    for (int i = 1; i < productsLines.size(); ++i) {
      std::string productLine = productsLines.at(i);

      std::cout << "|";

      std::cout.width(
          widthForId +
          2);  // +2 => because of the need to move the '|' to the right
      std::cout << std::right << "|";

      std::cout.width(
          widthForClient +
          2);  // +2 => because of the need to move the '|' to the right
      std::cout << std::right << "|";

      std::cout.width(widthForProducts);
      std::cout << std::right;
      std::cout << productLine << " |" << std::endl;
    }

    PrintHorizontalLine(out_, lineLength);
  }
}
