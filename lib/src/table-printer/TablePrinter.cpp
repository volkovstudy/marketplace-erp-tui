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

void TablePrinter::print(const std::vector<Client>& clients) {
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

void TablePrinter::print(const std::vector<Order>& orders) {
  std::map<const Order*, std::string> ids;
  std::map<const Order*, std::string> clients;
  std::map<const Order*, std::vector<std::string>> products;

  size_t max_id_len =
      std::ranges::max(orders | std::views::transform([&ids](const auto& o) {
                         std::string str = std::to_string(o.getId());
                         ids[&o] = str;
                         return str.length();
                       }));

  size_t max_client_len = std::ranges::max(
      orders | std::views::transform([&clients](const auto& o) {
        std::string str = makeClientLine(o.getClient());
        clients[&o] = str;
        return str.length();
      }));

  size_t max_product_len = std::ranges::max(
      orders | std::views::transform([&products](const auto& o) {
        auto lines = o.getProducts() | std::views::transform(makeProductLine);
        products[&o] = std::ranges::to<std::vector>(lines);
        return std::ranges::max(lines |
                                std::views::transform(&std::string::length));
      }));

  // indentLength * 2 => because of left & right indent
  // + 4 => because of four '|' characters in header
  // + 4 => because of spaces before '|' characters in header
  const size_t line_len = max_id_len + max_client_len + max_product_len +
                          (kIndentLength * 2) + 4 + 4;
  PrintHeader(out_, line_len, "*Orders*");

  out_ << '|';
  out_.width(max_id_len + kIndentLength);
  out_ << "ID " << " |";

  out_.width(max_client_len + 1);  // +1 => because of 1 space in " |"
  out_ << "CLIENT " << " |";

  out_.width(max_product_len + kIndentLength);
  out_ << "PRODUCTS " << " |";
  out_ << std::endl;

  PrintHorizontalLine(out_, line_len);

  const size_t id_width = max_id_len + kIndentLength;
  // +1 => because we need a space after previous '|' in ID column AND because
  // we don't have indent there
  const size_t client_width = max_client_len + 1;
  const size_t product_width = max_product_len + kIndentLength;

  for (auto& order : orders) {
    out_ << '|';

    out_.width(id_width);
    out_ << std::right << ids[&order] << " |";

    out_.width(client_width);
    out_ << std::right << clients[&order] << " |";

    const std::vector<std::string>& products_lines = products[&order];
    out_.width(product_width);
    out_ << std::right << (products_lines.empty() ? "" : products_lines.at(0))
         << " |" << kLineEnd;

    // Starts from 1 because we've already printed the first line
    for (size_t i = 1; i < products_lines.size(); ++i) {
      const std::string& product_line = products_lines.at(i);

      out_ << '|';

      // +2 => because of the need to move the '|' to the right
      out_.width(id_width + 2);
      out_ << std::right << '|';

      // +2 => because of the need to move the '|' to the right
      out_.width(client_width + 2);
      out_ << std::right << '|';

      out_.width(product_width);
      out_ << std::right;
      out_ << product_line << " |" << std::endl;
    }

    PrintHorizontalLine(out_, line_len);
  }
}
