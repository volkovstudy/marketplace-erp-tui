#include "table-printer/TablePrinter.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define indentLength 10

namespace {

void printHorizontalLine(int length) {
  for (int i = 0; i < length; ++i) {
    std::cout << "-";
  }
  std::cout << std::endl;
}

bool isOdd(int number) { return number % 2 != 0; }

void printTableName(const std::string& tableName, int lineLength) {
  int lengthOfIndent = lineLength / 2;

  bool isLengthOdd = isOdd(lineLength);
  if (isLengthOdd) lengthOfIndent++;

  std::cout << "|";
  std::cout.width(lengthOfIndent);
  std::cout << tableName;

  if (isLengthOdd)  // -1 / -2 => because begins printing after all width
    std::cout.width(lengthOfIndent - 2);
  else
    std::cout.width(lengthOfIndent - 1);
  std::cout << "|";
  std::cout << std::endl;
}

void printHeader(int lineLength, const std::string& tableName) {
  printHorizontalLine(lineLength);
  printTableName(tableName, lineLength);
  printHorizontalLine(lineLength);
}

std::string makeClientLine(Client& client) {
  std::stringstream clientLine;
  clientLine << client.getFullName() << " <" << client.getEmail() << ">";
  return clientLine.str();
}

std::string makeProductLine(Product* product) {
  int amount = product->getAmount();

  std::stringstream productLine;
  productLine << product->getName() << " - " << amount;

  if (amount == 1) {
    productLine << " unit";
  } else {
    productLine << " units";
  }

  return productLine.str();
}

}  // namespace

void TablePrinter::printVector(const std::vector<Client*>& clients) {
  int maxLengthOfName = 0, maxLengthOfEmail = 0;
  for (Client* client : clients) {
    int nameLength = (int)client->getFullName().length();
    maxLengthOfName = std::max(maxLengthOfName, nameLength);

    int emailLength = (int)client->getEmail().length();
    maxLengthOfEmail = std::max(maxLengthOfEmail, emailLength);
  }

  // indentLength * 2 => because of left & right indent
  // + 3 => because of three '|' characters in header
  int lineLength = maxLengthOfName + maxLengthOfEmail + (indentLength * 2) + 3;
  printHeader(lineLength, "*Clients*");

  std::cout << "|";
  std::cout.width(maxLengthOfName + indentLength);
  std::cout << "NAME " << " |";

  std::cout.width(maxLengthOfEmail + indentLength -
                  2);  // -2 => because of two spaces in next line
  std::cout << "EMAIL " << " |";
  std::cout << std::endl;

  printHorizontalLine(lineLength);

  for (Client* client : clients) {
    std::cout << "| ";
    std::cout.width(maxLengthOfName + indentLength - 1);
    std::cout << std::right;
    std::cout << client->getFullName();
    std::cout << " |";

    std::cout.width(maxLengthOfEmail + indentLength -
                    2);  // -2 => because of one space in " |" in NAME column &
                         // one space in the end
    std::cout << std::right;
    std::cout << client->getEmail();
    std::cout << " |" << std::endl;
  }

  printHorizontalLine(lineLength);
}

void TablePrinter::printVector(const std::vector<Order*>& orders) {
  std::map<Order*, std::string> idStrings;
  std::map<Order*, std::string> clientLines;
  std::map<Order*, std::vector<std::string>> productLines;

  int maxLengthOfId = 0, maxLengthOfClientLine = 0, maxLengthOfProductLine = 0;
  for (Order* order : orders) {
    std::string idString = std::to_string(order->getId());
    idStrings[order] = idString;
    int idLength = (int)idString.length();
    maxLengthOfId = std::max(maxLengthOfId, idLength);

    Client client = *(order->getClient());
    std::string clientLine = makeClientLine(client);
    clientLines[order] = clientLine;
    maxLengthOfClientLine =
        std::max(maxLengthOfClientLine, (int)clientLine.length());

    std::vector<std::string> productsLines;
    for (Product* product : order->getProducts()) {
      std::string productLine = makeProductLine(product);
      maxLengthOfProductLine =
          std::max(maxLengthOfProductLine, (int)productLine.length());

      productsLines.push_back(productLine);
    }
    productLines[order] = productsLines;
  }

  // indentLength * 2 => because of left & right indent
  // + 4 => because of four '|' characters in header
  // + 4 => because of spaces before '|' characters in header
  int lineLength = maxLengthOfId + maxLengthOfClientLine +
                   maxLengthOfProductLine + (indentLength * 2) + 4 + 4;
  printHeader(lineLength, "*Orders*");

  std::cout << "|";
  std::cout.width(maxLengthOfId + indentLength);
  std::cout << "ID " << " |";

  std::cout.width(maxLengthOfClientLine +
                  1);  // +1 => because of 1 space in " |"
  std::cout << "CLIENT " << " |";

  std::cout.width(maxLengthOfProductLine + indentLength);
  std::cout << "PRODUCTS " << " |";
  std::cout << std::endl;

  printHorizontalLine(lineLength);

  int widthForId = maxLengthOfId + indentLength;
  // +1 => because we need a space after previous '|' in ID column AND because
  // we don't have indent there
  int widthForClient = maxLengthOfClientLine + 1;
  int widthForProducts = maxLengthOfProductLine + indentLength;

  for (Order* order : orders) {
    std::cout << "|";

    std::cout.width(widthForId);
    std::cout << std::right << idStrings[order] << " |";

    std::cout.width(widthForClient);
    std::cout << std::right << clientLines[order] << " |";

    std::vector<std::string> productsLines = productLines[order];
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

    printHorizontalLine(lineLength);
  }
}
