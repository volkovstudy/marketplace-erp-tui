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

namespace {

void printSectionVariants() {
  std::cout << "What do you want to do?" << std::endl << std::endl;

  std::cout << "(A)dd new order;" << std::endl;
  std::cout << "(L)ist all orders;" << std::endl;
  std::cout << "(Q)uit from the section;" << std::endl;
}

}  // namespace

void OrdersDialog::openManagementDialog() {
  std::cout << "You opened orders management section. ";
  printSectionVariants();

  do {
    bool isUserWantToLeft = getChoiceAndExecuteActionAndReturnQuitResult();

    if (isUserWantToLeft) {
      utils::PrintDelimiter(std::cout);
      return;
    }

    utils::PrintDelimiter(std::cout);

    std::cout << "You came back to the orders management section." << std::endl;
    printSectionVariants();
  } while (true);
}

void OrdersDialog::addNewOrder() {
  OrderAddingDialog dialog;
  dialog.addOrder();
}

void OrdersDialog::listAllOrders() {
  CsvFileService clients_csv(pathToClientsFile),
      products_csv(pathToProductsFile), orders_csv(pathToOrdersFile);

  ClientRepository client_repo(clients_csv);
  ProductsRepository products_repo(products_csv);
  OrderRepository order_repo(orders_csv, client_repo, products_repo);

  const std::vector<Order>& orders = order_repo.getAll();

  if (orders.empty()) {
    std::cout << "There are no orders!" << std::endl;
    return;
  }

  std::cout << "All orders:" << std::endl;
  TablePrinter printer(std::cout);
  printer.print(orders);

  std::cout << std::endl << "What do you want to do?" << std::endl;
  std::cout << "(Q)uit;" << std::endl;

  do {
    std::cout << std::endl << "Your choice (Q): ";

    std::string program;
    std::cin >> program;
    utils::toLowerCase(program);

    if (program == quitProgramChar) {
      return;
    } else {
      std::cout << std::endl << "Wrong input. Try again." << std::endl;
    }
  } while (true);
}

bool OrdersDialog::getChoiceAndExecuteActionAndReturnQuitResult() {
  do {
    std::cout << std::endl << "Your choice (A, L, Q): ";

    std::string program;
    std::cin >> program;
    utils::toLowerCase(program);

    if (program == addNewOrderProgramChar) {
      utils::PrintDelimiter(std::cout);
      addNewOrder();
      break;
    } else if (program == listAllOrdersProgramChar) {
      utils::PrintDelimiter(std::cout);
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
