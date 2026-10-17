#include <gtest/gtest.h>

#include <format>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "models/Client.h"
#include "table-printer/TablePrinter.h"

namespace {

std::vector<Client> givenFourClients() {
  std::vector<Client> clients;
  clients.emplace_back("Very long testing name",
                       "very.long.testing.email@example.com");
  clients.emplace_back(
      "Very very very long name for testing class",
      "very.very.very.long.email.for.testing.class@example.com");
  clients.emplace_back("Test name", "test@example.com");
  clients.emplace_back("Petr", "petya@example.com");

  return clients;
}

std::vector<Order> givenFourOrders() {
  std::vector<Order> orders;
  std::vector<Client> clients = givenFourClients();

  std::vector<Product> products1;
  products1.emplace_back("tomato", 5);
  products1.emplace_back("cucumbers", 2);
  orders.emplace_back(1, clients.at(0), products1);

  std::vector<Product> products2;
  products2.emplace_back("tv", 1);
  products2.emplace_back("playstation", 1);
  orders.emplace_back(2, clients.at(1), products2);

  std::vector<Product> products3;
  products3.emplace_back("table", 1);
  orders.emplace_back(3, clients.at(2), products3);

  std::vector<Product> products4;
  products4.emplace_back("Long product", 1000);
  orders.emplace_back(4, clients.at(3), products4);

  return orders;
}

template <typename C, typename T>
concept has_print_vector_for = requires(C c, T arg) { c.printVector(arg); };

template <typename T>
  requires has_print_vector_for<TablePrinter, T>
std::string Render(const T& data) {
  std::ostringstream out;

  TablePrinter printer(out);
  printer.printVector(data);

  return out.str();
}

std::vector<std::string> SplitLines(const std::string& str) {
  std::vector<std::string> lines;

  std::istringstream in{str};
  for (std::string line; std::getline(in, line);) {
    lines.push_back(std::move(line));
  }

  return lines;
}

}  // namespace

TEST(TablePrinterTests, PrintClients) {
  std::vector<Client> clients = givenFourClients();
  TablePrinter printer(std::cout);

  printer.printVector(clients);
}

TEST(TablePrinterTests, AllLinesHasTheSameWidthInClients) {
  const auto lines = SplitLines(Render(givenFourClients()));

  ASSERT_FALSE(lines.empty());

  const size_t length = lines.front().length();
  for (const auto& line : lines) {
    ASSERT_EQ(line.length(), length) << std::format("line: [{}]", line);
  }
}

TEST(TablePrinterTests, printOrders) {
  std::vector<Order> orders = givenFourOrders();

  TablePrinter printer(std::cout);
  printer.printVector(orders);
}
