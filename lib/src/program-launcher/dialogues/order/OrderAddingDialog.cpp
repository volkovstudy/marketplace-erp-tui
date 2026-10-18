#include "program-launcher/dialogues/order/OrderAddingDialog.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "models/Client.h"
#include "models/Order.h"
#include "repositories/ClientRepository.h"
#include "repositories/OrderRepository.h"
#include "repositories/ProductsRepository.h"
#include "utils/Utils.h"

#define pathToClientsFile "marketplace-erp/clients.csv"
#define pathToOrdersFile "marketplace-erp/orders.csv"
#define pathToProductsFile "marketplace-erp/products.csv"

#define yesChar "y"
#define noChar "n"
#define editChar "e"
#define cancelChar "c"

namespace {

std::vector<Client>& getAllClients() {
  CsvFileService csv_file_service(pathToClientsFile);
  ClientRepository clientRepository(csv_file_service);

  return clientRepository.getAll();
}

std::string makeClientLine(const Client& client) {
  std::stringstream clientLine;
  clientLine << client.getFullName() << " <" << client.getEmail() << ">";

  return clientLine.str();
}

void printAllClients() {
  const std::vector<Client>& clients = getAllClients();

  std::vector<std::string> clientLines;
  for (int i = 0; i < clients.size(); ++i) {
    Client client = clients.at(i);

    std::string clientLine = makeClientLine(client);

    std::stringstream fullClientLine;
    int clientNo = i + 1;
    fullClientLine << clientNo << ") " << clientLine;

    clientLines.push_back(fullClientLine.str());
  }

  for (const std::string& line : clientLines) {
    std::cout << line << std::endl;
  }
}

void readAndSaveProduct(std::vector<Product>& products) {
  std::string name;
  std::cout << "Name: ";
  do {
    std::getline(std::cin, name);
  } while (name.empty());

  int amount;
  do {
    std::cout << "Amount: ";

    std::string inputAmount;
    std::cin >> inputAmount;

    try {
      amount = stoi(inputAmount);
    } catch (std::invalid_argument& invalidArgument) {
      amount = -1;
      std::cout << "Write a number!" << std::endl;
    } catch (std::out_of_range& outOfRange) {
      amount = -1;
      std::cout << "Write a smaller number!" << std::endl;
    }
  } while (amount < 0);

  products.emplace_back(name, amount);
}

void getInformationAboutOrder(Client& client, std::vector<Product>& products) {
  const std::vector<Client>& clients = getAllClients();

  if (clients.empty()) {
    throw *new std::exception;
  }

  std::cout << "All clients:" << std::endl;
  printAllClients();
  int clientNo;
  do {
    std::cout << "Choose a client (" << 1 << "-" << clients.size() << "): ";

    std::string inputClientNo;
    std::cin >> inputClientNo;

    try {
      clientNo = std::stoi(inputClientNo);
    } catch (std::invalid_argument& invalidArgument) {
      clientNo = -1;
      std::cout << "Write a number!" << std::endl;
    } catch (std::out_of_range& outOfRange) {
      clientNo = -1;
      std::cout << "Write a smaller number!" << std::endl;
    }
    clientNo -= 1;  // -1 => because in printing clients using index+1
  } while (clientNo < 0 || clientNo > clients.size());

  client = clients.at(clientNo);

  std::cout << std::endl << "Write the products: " << std::endl;

  readAndSaveProduct(products);

  do {
    std::cout << std::endl << "Do you want to add one more? (Y/N): ";

    std::string program;
    std::cin >> program;
    utils::toLowerCase(program);

    if (program == yesChar) {
      std::cout << std::endl;
      readAndSaveProduct(products);
    } else if (program == noChar) {
      return;
    } else {
      std::cout << std::endl << "Wrong input. Try again." << std::endl;
    }
  } while (true);
}

void printProducts(const std::vector<Product>& products) {
  for (auto& product : products) {
    int amount = product.getAmount();

    std::cout << product.getName() << " - " << amount;

    if (amount == 1)
      std::cout << " unit";
    else
      std::cout << " units";

    std::cout << std::endl;
  }
}

void saveOrder(Order& order) {
  CsvFileService clients_csv(pathToClientsFile),
      products_csv(pathToProductsFile), orders_csv(pathToOrdersFile);

  ClientRepository client_repo(clients_csv);
  ProductsRepository products_repo(products_csv);
  OrderRepository orderRepository(orders_csv, client_repo, products_repo);

  orderRepository.save(order);
}

}  // namespace

void OrderAddingDialog::addOrder() {
  std::cout << "Now you're going to add new order." << std::endl << std::endl;

  Client& client = *new Client(-1, "", "");
  std::vector<Product> products{};

  try {
    getInformationAboutOrder(client, products);
  } catch (std::exception& exception) {
    std::cout << "There are no clients! Add new client!" << std::endl;
    return;
  }

  do {
    utils::PrintDelimiter(std::cout);

    std::cout << "Well, check the information about new order:" << std::endl
              << std::endl;
    std::cout << "Client:" << std::endl
              << makeClientLine(client) << std::endl
              << std::endl;
    std::cout << "Products:" << std::endl;
    printProducts(products);

    std::cout << std::endl << "Is it right?" << std::endl;
    std::cout << "(Y)es, (E)dit, (C)ancel: ";

    std::string program;
    std::cin >> program;
    utils::toLowerCase(program);

    if (program == yesChar) {
      Order order(client, products);
      saveOrder(order);

      std::cout << std::endl << "Order saved." << std::endl;

      break;
    } else if (program == editChar) {
      utils::PrintDelimiter(std::cout);

      products = {};

      getInformationAboutOrder(client, products);
    } else if (program == cancelChar) {
      std::cout << std::endl << "You left adding new order." << std::endl;
      return;
    } else {
      std::cout << std::endl << "Wrong input. Try again." << std::endl;
    }
  } while (true);
}
