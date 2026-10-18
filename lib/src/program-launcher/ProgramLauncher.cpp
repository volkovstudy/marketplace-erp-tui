#include "program-launcher/ProgramLauncher.h"

#include <istream>
#include <ostream>
#include <string>

#include "program-launcher/dialogues/client/ClientDialog.h"
#include "program-launcher/dialogues/order/OrdersDialog.h"
#include "utils/Utils.h"

const static std::string kClientsManagementProgram = "c";
const static std::string kOrdersManagementProgram = "o";
const static std::string kQuitProgram = "q";

ProgramLauncher::ProgramLauncher(std::ostream& out, std::istream& in)
    : out_(out), in_(in) {}

void ProgramLauncher::start() {
  out_ << "Hello! ";
  printProgramSections();

  while (true) {
    bool doesUserWantToLeft = handleUserChoice();
    if (doesUserWantToLeft) return;

    out_ << "You came back to the main section." << std::endl;
    printProgramSections();
  }
}

void ProgramLauncher::printProgramSections() {
  out_ << "What do you want to open?" << std::endl << std::endl;

  out_ << "(C)lients management;" << std::endl;
  out_ << "(O)rders management;" << std::endl;
  out_ << "(Q)uit;" << std::endl;
}

bool ProgramLauncher::handleUserChoice() {
  while (true) {
    out_ << std::endl << "Your choice (C, O, Q): ";

    std::string program;
    in_ >> program;
    utils::toLowerCase(program);

    if (program == kClientsManagementProgram) {
      utils::PrintDelimiter(out_);

      ClientDialog dialog(out_, in_, client_repo_);
      dialog.openManagement();

      return false;
    } else if (program == kOrdersManagementProgram) {
      utils::PrintDelimiter(out_);

      OrdersDialog dialog;
      dialog.openManagementDialog();

      return false;
    } else if (program == kQuitProgram) {
      out_ << std::endl << "Bye!" << std::endl;
      return true;
    } else {
      out_ << std::endl << "Wrong input. Try again." << std::endl;
    }
  }
}
