#include "table-printer/TablePrinter.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <ostream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "models/Client.h"
#include "models/Order.h"

namespace {

constexpr size_t kLeftIndent = 10;
constexpr size_t kRightIndent = 1;

constexpr char kLineEnd = '\n';

template <std::size_t N>
using Line = std::array<std::string, N>;

template <std::size_t N>
using Record = std::vector<Line<N>>;

template <std::size_t N>
using Widths = std::array<std::size_t, N>;

void PrintHorizontalLine(std::ostream& out, size_t length) {
  out << std::string(length, '-') << kLineEnd;
}

void PrintTableName(std::ostream& out, std::string_view table_name,
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
                 std::string_view table_name) {
  PrintHorizontalLine(out, line_length);
  PrintTableName(out, table_name, line_length);
  PrintHorizontalLine(out, line_length);
}

template <std::size_t N>
Widths<N> ComputeWidths(const Line<N>& header,
                        const std::vector<Record<N>>& records) {
  Widths<N> widths{};

  auto widen = [&widths](const Line<N>& line) {
    for (auto [w, cell] : std::views::zip(widths, line)) {
      w = std::max(w, cell.length());
    }
  };

  widen(header);

  std::ranges::for_each(records | std::views::join, widen);

  return widths;
}

template <std::size_t N>
std::size_t ComputeLineLength(const Widths<N>& widths) {
  constexpr size_t separators = N + 1;
  constexpr size_t indents = (kLeftIndent + kRightIndent) * N;

  const size_t values = std::ranges::fold_left(widths, 0uz, std::plus{});

  return values + indents + separators;
}

template <std::size_t N>
void PrintLine(std::ostream& out, const Widths<N>& widths,
               const Line<N>& line) {
  for (auto [width, cell] : std::views::zip(widths, line)) {
    std::print(out, "|{0:>{1}}{2:>{3}}", cell, width + kLeftIndent, "",
               kRightIndent);
  }

  std::print(out, "|{}", kLineEnd);
}

template <std::size_t N>
void PrintTable(std::ostream& out, std::string_view table_name,
                const Line<N>& header, const std::vector<Record<N>>& records) {
  const auto widths = ComputeWidths(header, records);
  const std::size_t line_length = ComputeLineLength(widths);

  PrintHeader(out, line_length, table_name);
  PrintLine(out, widths, header);
  PrintHorizontalLine(out, line_length);

  for (const auto& record : records) {
    for (const auto& line : record) {
      PrintLine(out, widths, line);
    }
    PrintHorizontalLine(out, line_length);
  }
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

Record<3> MakeRecord(const Order& order) {
  const auto& products = order.getProducts();

  Record<3> lines(std::max(products.size(), 1uz));
  lines[0][0] = std::to_string(order.getId());
  lines[0][1] = MakeClientLine(order.getClient());

  for (auto [line, product] : std::views::zip(lines, products)) {
    line[2] = MakeProductLine(product);
  }

  return lines;
}

Record<2> MakeRecord(const Client& client) {
  Record<2> record(1);
  record[0][0] = client.getFullName();
  record[0][1] = client.getEmail();

  return record;
}

}  // namespace

TablePrinter::TablePrinter(std::ostream& out) : out_(out) {}

void TablePrinter::print(const std::vector<Client>& clients) {
  const auto records =
      clients |
      std::views::transform([](const auto& c) { return MakeRecord(c); }) |
      std::ranges::to<std::vector>();

  PrintTable<2>(out_, "*Clients*", {"NAME", "EMAIL"}, records);
}

void TablePrinter::print(const std::vector<Order>& orders) {
  const auto records =
      orders |
      std::views::transform([](const auto& o) { return MakeRecord(o); }) |
      std::ranges::to<std::vector>();

  PrintTable<3>(out_, "*Orders*", {"ID", "CLIENT", "PRODUCTS"}, records);
}
