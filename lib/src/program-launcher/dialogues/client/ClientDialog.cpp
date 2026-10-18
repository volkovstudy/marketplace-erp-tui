#include "program-launcher/dialogues/client/ClientDialog.h"

#include <algorithm>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "program-launcher/dialogues/client/ClientAddingDialog.h"
#include "repositories/ClientRepository.h"
#include "table-printer/TablePrinter.h"
#include "utils/Utils.h"

const static char kAddNewClientProgramChar = 'a';
const static char kListAllClientsProgramChar = 'l';
const static char kQuitProgramChar = 'q';

const static char kYesChar = 'y';
const static char kEditChar = 'e';
const static char kCancelChar = 'c';

ClientDialog::ClientDialog(std::ostream& out, std::istream& in,
                           ClientRepository& repo)
    : out_(out), in_(in), repo_(repo) {}

void ClientDialog::openManagement() {
  out_ << "You opened clients management section. ";
  printSectionVariants();

  while (true) {
    bool isUserWantToLeft = handleUserChoice();

    if (isUserWantToLeft) {
      utils::PrintDelimiter(out_);
      return;
    }

    utils::PrintDelimiter(out_);

    out_ << "You came back to the clients management section." << std::endl;
    printSectionVariants();
  }
}

void ClientDialog::addNewClient() {
  ClientAddingDialog dialog(out_, in_, repo_);
  dialog.addClient();
}

void ClientDialog::listAllClients() {
  const std::vector<Client>& clients = repo_.getAll();

  if (clients.empty()) {
    out_ << "There are no clients!" << std::endl;
    return;
  }

  out_ << "All clients:" << std::endl;
  TablePrinter printer(out_);
  printer.print(clients);

  out_ << std::endl << "What do you want to do?" << std::endl;
  out_ << "(Q)uit;" << std::endl;

  while (true) {
    out_ << std::endl << "Your choice (Q): ";

    std::string input;
    in_ >> input;

    if (input.empty()) {
      out_ << std::endl << "Wrong input. Try again." << std::endl;
    }

    char program = std::tolower(input[0]);

    switch (program) {
      case kQuitProgramChar:
        return;

      default:
        out_ << std::endl << "Wrong input. Try again." << std::endl;
    }
  }
}

void ClientDialog::printSectionVariants() {
  out_ << "What do you want to do?" << std::endl << std::endl;

  out_ << "(A)dd new client;" << std::endl;
  out_ << "(L)ist all clients;" << std::endl;
  out_ << "(Q)uit from the section;" << std::endl;
}

bool ClientDialog::handleUserChoice() {
  while (true) {
    out_ << std::endl << "Your choice (A, L, Q): ";

    std::string input;
    in_ >> input;

    if (input.empty()) {
      out_ << std::endl << "Wrong input. Try again." << std::endl;
    }

    char program = std::tolower(input[0]);

    switch (program) {
      case kAddNewClientProgramChar:
        utils::PrintDelimiter(out_);
        addNewClient();
        return false;

      case kListAllClientsProgramChar:
        utils::PrintDelimiter(out_);
        listAllClients();
        return false;

      case kQuitProgramChar:
        out_ << std::endl
             << "You left clients management section." << std::endl;
        return true;

      default:
        out_ << std::endl << "Wrong input. Try again." << std::endl;
    }
  }
}
