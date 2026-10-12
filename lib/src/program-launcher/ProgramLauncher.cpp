#include "program-launcher/ProgramLauncher.h"

#include <iostream>
#include <string>

#include "program-launcher/dialogues/client/ClientDialog.h"
#include "program-launcher/dialogues/order/OrdersDialog.h"
#include "utils/Utils.h"

#define clientsManagementProgram "c"
#define ordersManagementProgram "o"
#define quitProgram "q"

namespace {

void printProgramSections() {
  std::cout << "What do you want to open?" << std::endl << std::endl;

  std::cout << "(C)lients management;" << std::endl;
  std::cout << "(O)rders management;" << std::endl;
  std::cout << "(Q)uit;" << std::endl;
}

bool getChoiceAndExecuteActionAndReturnQuitResult() {
  do {
    std::cout << std::endl << "Your choice (C, O, Q): ";

    std::string program;
    std::cin >> program;
    utils::toLowerCase(&program);

    if (program == clientsManagementProgram) {
      utils::printDelimiter();

      ClientDialog dialog;
      dialog.openManagementDialog();

      break;
    } else if (program == ordersManagementProgram) {
      utils::printDelimiter();

      OrdersDialog dialog;
      dialog.openManagementDialog();

      break;
    } else if (program == quitProgram) {
      std::cout << std::endl << "Bye!" << std::endl;
      return true;
    } else {
      std::cout << std::endl << "Wrong input. Try again." << std::endl;
    }
  } while (true);

  return false;
}

}  // namespace

void ProgramLauncher::start() {
  std::cout << "Hello! ";
  printProgramSections();

  while (true) {
    bool doesUserWantToLeft = getChoiceAndExecuteActionAndReturnQuitResult();
    if (doesUserWantToLeft) return;

    std::cout << "You came back to the main section." << std::endl;
    printProgramSections();
  }
}
