#include "table-printer/TablePrinter.h"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <ostream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

#include "models/Client.h"
#include "models/Order.h"

namespace {

constexpr size_t kLeftIndent = 10;
constexpr size_t kRightIndent = 1;

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

struct Column {
  std::string name;
  size_t width;
};

template <typename T>
Column MakeColumn(const std::string& name, const std::vector<T>& data,
                  auto getter) {
  const size_t width = std::ranges::fold_left(
      data, name.length(), [&getter](size_t w, const T& o) {
        return std::max(w, std::invoke(getter, o).length());
      });

  return Column{name, width};
}

size_t ComputeLineLength(const std::vector<Column>& columns) {
  const size_t separators = columns.size() + 1;
  const size_t indents = (kLeftIndent + kRightIndent) * columns.size();

  const auto values_view = columns | std::views::transform(&Column::width);
  const size_t values =
      std::ranges::fold_left(values_view, size_t{0}, std::plus{});

  return values + indents + separators;
}

void PrintRow(std::ostream& out, const std::vector<Column>& columns,
              const std::vector<std::string>& values) {
  for (auto [column, value] : std::views::zip(columns, values)) {
    std::print(out, "|{0:>{1}}{2:>{3}}", value, column.width + kLeftIndent, "",
               kRightIndent);
  }

  out << '|' << kLineEnd;
}

void PrintColumnNames(std::ostream& out, const std::vector<Column>& columns) {
  auto names = std::ranges::to<std::vector>(
      std::views::transform(columns, &Column::name));

  PrintRow(out, columns, names);
}

}  // namespace

TablePrinter::TablePrinter(std::ostream& out) : out_(out) {}

void TablePrinter::print(const std::vector<Client>& clients) {
  const auto columns =
      std::vector<Column>{MakeColumn("NAME", clients, &Client::getFullName),
                          MakeColumn("EMAIL", clients, &Client::getEmail)};

  const size_t line_length = ComputeLineLength(columns);

  PrintHeader(out_, line_length, "*Clients*");
  PrintColumnNames(out_, columns);
  PrintHorizontalLine(out_, line_length);

  for (const auto& client : clients) {
    PrintRow(out_, columns, {client.getFullName(), client.getEmail()});
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

                      return Row{std::move(id), std::move(client), products};
                    }) |
                    std::ranges::to<std::vector>();

  const auto columns = std::vector<Column>{
      MakeColumn("ID", rows, &Row::id),
      MakeColumn("CLIENT", rows, &Row::client),
      MakeColumn("PRODUCTS", rows, [](const Row& row) -> std::string {
        if (row.products.empty()) return {};
        return std::ranges::max(row.products, std::ranges::less{},
                                std::ranges::size);
      })};

  const size_t line_length = ComputeLineLength(columns);

  PrintHeader(out_, line_length, "*Orders*");
  PrintColumnNames(out_, columns);
  PrintHorizontalLine(out_, line_length);

  for (const auto& row : rows) {
    const std::vector<std::string>& products = row.products;

    const std::string first_line =
        products.empty() ? std::string{""} : products.front();

    PrintRow(out_, columns, {row.id, row.client, first_line});

    for (const auto& line : products | std::views::drop(1)) {
      PrintRow(out_, columns, {"", "", line});
    }

    PrintHorizontalLine(out_, line_length);
  }
}
