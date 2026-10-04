#include "program-launcher/dialogues/order/OrdersDialog.h"

#include <iostream>
#include <string>
#include <vector>

#include "program-launcher/dialogues/order/OrderAddingDialog.h"
#include "repositories/ClientRepository.h"
#include "repositories/OrderRepository.h"
#include "table-printer/TablePrinter.h"
#include "utils/Utils.h"

#define pathToClientsFile "marketplace-erp/clients.csv"
#define pathToOrdersFile "marketplace-erp/orders.csv"
#define pathToProductsFile "marketplace-erp/products.csv"

#define addNewOrderProgramChar "a"
#define listAllOrdersProgramChar "l"
#define quitProgramChar "q"

void OrdersDialog::openManagementDialog() {
  std::cout << "You opened orders management section. ";
  printSectionVariants();

  do {
    bool isUserWantToLeft = getChoiceAndExecuteActionAndReturnQuitResult();

    if (isUserWantToLeft) {
      Utils::printDelimiter();
      return;
    }

    Utils::printDelimiter();

    std::cout << "You came back to the orders management section." << std::endl;
    printSectionVariants();
  } while (true);
}

void OrdersDialog::printSectionVariants() {
  std::cout << "What do you want to do?" << std::endl << std::endl;

  std::cout << "(A)dd new order;" << std::endl;
  std::cout << "(L)ist all orders;" << std::endl;
  std::cout << "(Q)uit from the section;" << std::endl;
}

bool OrdersDialog::getChoiceAndExecuteActionAndReturnQuitResult() {
  do {
    std::cout << std::endl << "Your choice (A, L, Q): ";

    std::string program;
    std::cin >> program;
    Utils::toLowerCase(&program);

    if (program == addNewOrderProgramChar) {
      Utils::printDelimiter();
      addNewOrder();
      break;
    } else if (program == listAllOrdersProgramChar) {
      Utils::printDelimiter();
      listAllOrders();
      break;
    } else if (program == quitProgramChar) {
      std::cout << std::endl
                << "You left orders management section." << std::endl;
      return true;
    } else {
      std::cout << std::endl << "Wrong input. Try again." << std::endl;
    }
  } while (true);

  return false;
}

void OrdersDialog::addNewOrder() { OrderAddingDialog::addOrder(); }

void OrdersDialog::listAllOrders() {
  ClientRepository clientRepository(pathToClientsFile);
  ProductsRepository productsRepository(pathToProductsFile);
  OrderRepository orderRepository(pathToOrdersFile, &clientRepository,
                                  &productsRepository);

  std::vector<Order*> orders = orderRepository.getAll();

  if (orders.empty()) {
    std::cout << "There are no orders!" << std::endl;
    return;
  }

  std::cout << "All orders:" << std::endl;
  TablePrinter::printVector(orders);

  std::cout << std::endl << "What do you want to do?" << std::endl;
  std::cout << "(Q)uit;" << std::endl;

  do {
    std::cout << std::endl << "Your choice (Q): ";

    std::string program;
    std::cin >> program;
    Utils::toLowerCase(&program);

    if (program == quitProgramChar) {
      return;
    } else {
      std::cout << std::endl << "Wrong input. Try again." << std::endl;
    }
  } while (true);
}
