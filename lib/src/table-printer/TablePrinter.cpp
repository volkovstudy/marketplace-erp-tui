#include "table-printer/TablePrinter.h"

#include <algorithm>
#include <cstddef>
#include <ostream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

#include "models/Client.h"
#include "models/Order.h"

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

  std::print(out, "|{:>{}}", table_name, indent_length);

  if (is_length_odd) {  // -1 / -2 => because begins printing after all width
    indent_length -= 2;
  } else {
    indent_length -= 1;
  }

  std::print(out, "{:>{}}{}", "|", indent_length, kLineEnd);
}

void PrintHeader(std::ostream& out, size_t line_length,
                 const std::string& table_name) {
  PrintHorizontalLine(out, line_length);
  PrintTableName(out, table_name, line_length);
  PrintHorizontalLine(out, line_length);
}

std::string MakeClientLine(const Client& client) {
  std::ostringstream line;
  line << client.getFullName() << " <" << client.getEmail() << ">";
  return line.str();
}

std::string MakeProductLine(const Product& product) {
  int amount = product.getAmount();

  std::ostringstream line;
  line << product.getName() << " - " << amount;

  if (amount == 1) {
    line << " unit";
  } else {
    line << " units";
  }

  return line.str();
}

}  // namespace

TablePrinter::TablePrinter(std::ostream& out) : out_(out) {}

void TablePrinter::print(const std::vector<Client>& clients) {
  struct MaxLengths {
    size_t name;
    size_t email;
  };

  auto max_lengths = std::ranges::fold_left(
      clients, MaxLengths{}, [](MaxLengths w, const auto& c) {
        w.name = std::max(w.name, c.getFullName().length());
        w.email = std::max(w.email, c.getEmail().length());
        return w;
      });

  // indentLength * 2 => because of left & right indent
  // + 3 => because of three '|' characters in header
  const size_t line_length =
      max_lengths.name + max_lengths.email + (kIndentLength * 2) + 3;
  PrintHeader(out_, line_length, "*Clients*");

  const size_t name_header_width = max_lengths.name + kIndentLength;
  std::print(out_, "|{:>{}} |", "NAME", name_header_width);

  // -2 => because of two spaces in next line
  const size_t email_header_width = max_lengths.email + kIndentLength - 2;
  std::print(out_, "{:>{}} |{}", "EMAIL", email_header_width, kLineEnd);

  PrintHorizontalLine(out_, line_length);

  const size_t name_width = max_lengths.name + kIndentLength;
  // -2 => because of one space in " |" in NAME column &  one space in the end
  const size_t email_width = max_lengths.email + kIndentLength - 2;

  for (const auto& client : clients) {
    std::print(out_, "|{:>{}} |", client.getFullName(), name_width);
    std::print(out_, "{:>{}} |{}", client.getEmail(), email_width, kLineEnd);
  }

  PrintHorizontalLine(out_, line_length);
}

void TablePrinter::print(const std::vector<Order>& orders) {
  struct Row {
    std::string id;
    std::string client;
    std::vector<std::string> products;
  };

  const auto rows = orders | std::views::transform([](const auto& o) {
                      std::string id = std::to_string(o.getId());
                      std::string client = MakeClientLine(o.getClient());
                      auto products = o.getProducts() |
                                      std::views::transform(MakeProductLine) |
                                      std::ranges::to<std::vector>();

                      return Row{id, client, products};
                    });

  struct MaxLengths {
    size_t id;
    size_t client;
    size_t product;
  };

  auto max_len = std::ranges::fold_left(
      rows, MaxLengths{}, [](MaxLengths l, const Row& r) {
        l.id = std::max(l.id, r.id.length());
        l.client = std::max(l.client, r.client.length());
        l.product = std::ranges::fold_left(r.products, l.product,
                                           [](std::size_t s, const auto& p) {
                                             return std::max(s, p.length());
                                           });

        return l;
      });

  // indentLength * 2 => because of left & right indent
  // + 4 => because of four '|' characters in header
  // + 4 => because of spaces before '|' characters in header
  const size_t line_len = max_len.id + max_len.client + max_len.product +
                          (kIndentLength * 2) + 4 + 4;
  PrintHeader(out_, line_len, "*Orders*");

  const size_t id_header_width = max_len.id + kIndentLength;
  std::print(out_, "|{:>{}} |", "ID", id_header_width);

  // +1 => because of 1 space in " |"
  const size_t client_header_width = max_len.client + 1;
  std::print(out_, "{:>{}} |", "CLIENT", client_header_width);

  const size_t products_header_width = max_len.product + kIndentLength;
  std::print(out_, "{:>{}} |{}", "PRODUCTS", products_header_width, kLineEnd);

  PrintHorizontalLine(out_, line_len);

  const size_t id_width = max_len.id + kIndentLength;
  // +1 => because we need a space after previous '|' in ID column AND because
  // we don't have indent there
  const size_t client_width = max_len.client + 1;
  const size_t product_width = max_len.product + kIndentLength;

  // +1 => because of the need to move the '|' to the right
  const size_t empty_id_width = id_width + 1;
  const size_t empty_client_width = client_width + 1;

  for (const auto& row : rows) {
    std::print(out_, "|{:>{}} |", row.id, id_width);
    std::print(out_, "{:>{}} |", row.client, client_width);

    const std::vector<std::string>& products = row.products;

    const std::string_view first_line =
        products.empty() ? std::string_view{} : products.front();
    std::print(out_, "{:>{}} |{}", first_line, product_width, kLineEnd);

    for (const auto& line : products | std::views::drop(1)) {
      std::print(out_, "|{:>{}}|", "", empty_id_width);
      std::print(out_, "{:>{}}|", "", empty_client_width);
      std::print(out_, "{:>{}} |{}", line, product_width, kLineEnd);
    }

    PrintHorizontalLine(out_, line_len);
  }
}
