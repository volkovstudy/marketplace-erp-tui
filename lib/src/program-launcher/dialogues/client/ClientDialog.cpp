#include "program-launcher/dialogues/client/ClientDialog.h"

#include <iostream>
#include <string>
#include <vector>

#include "program-launcher/dialogues/client/ClientAddingDialog.h"
#include "repositories/ClientRepository.h"
#include "table-printer/TablePrinter.h"
#include "utils/Utils.h"

#define pathToClientsFile "marketplace-erp/clients.csv"

#define addNewClientProgramChar "a"
#define listAllClientsProgramChar "l"
#define quitProgramChar "q"

#define yesChar "y"
#define editChar "e"
#define cancelChar "c"

namespace {

void printSectionVariants() {
  std::cout << "What do you want to do?" << std::endl << std::endl;

  std::cout << "(A)dd new client;" << std::endl;
  std::cout << "(L)ist all clients;" << std::endl;
  std::cout << "(Q)uit from the section;" << std::endl;
}

}  // namespace

void ClientDialog::openManagementDialog() {
  std::cout << "You opened clients management section. ";
  printSectionVariants();

  do {
    bool isUserWantToLeft = getChoiceAndExecuteActionAndReturnQuitResult();

    if (isUserWantToLeft) {
      utils::printDelimiter();
      return;
    }

    utils::printDelimiter();

    std::cout << "You came back to the clients management section."
              << std::endl;
    printSectionVariants();
  } while (true);
}

void ClientDialog::addNewClient() {
  ClientAddingDialog dialog;
  dialog.addClient();
}

void ClientDialog::listAllClients() {
  ClientRepository clientRepository(pathToClientsFile);
  std::vector<Client*> clients = clientRepository.getAll();

  if (clients.empty()) {
    std::cout << "There are no clients!" << std::endl;
    return;
  }

  std::cout << "All clients:" << std::endl;
  TablePrinter printer;
  printer.printVector(clients);

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

bool ClientDialog::getChoiceAndExecuteActionAndReturnQuitResult() {
  do {
    std::cout << std::endl << "Your choice (A, L, Q): ";

    std::string program;
    std::cin >> program;
    utils::toLowerCase(program);

    if (program == addNewClientProgramChar) {
      utils::printDelimiter();
      addNewClient();
      break;
    } else if (program == listAllClientsProgramChar) {
      utils::printDelimiter();
      listAllClients();
      break;
    } else if (program == quitProgramChar) {
      std::cout << std::endl
                << "You left clients management section." << std::endl;
      return true;
    } else {
      std::cout << std::endl << "Wrong input. Try again." << std::endl;
    }
  } while (true);

  return false;
}
