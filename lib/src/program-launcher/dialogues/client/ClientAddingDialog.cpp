#include "program-launcher/dialogues/client/ClientAddingDialog.h"

#include <iostream>
#include <string>
#include <utility>

#include "models/Client.h"
#include "repositories/ClientRepository.h"
#include "utils/Utils.h"

namespace {

const static char kTab = '\t';

const static char yesChar = 'y';
const static char editChar = 'e';
const static char cancelChar = 'c';

}  // namespace

ClientAddingDialog::ClientAddingDialog(std::ostream& out, std::istream& in,
                                       ClientRepository& repo)
    : out_(out), in_(in), repo_(repo) {}

void ClientAddingDialog::addClient() {
  out_ << "Now you're going to add new client." << std::endl;

  Client client = readClientDetails();

  while (true) {
    utils::PrintDelimiter(out_);

    out_ << "Well, check the information about new client:" << std::endl;
    out_ << "Name" << kTab << client.getFullName() << std::endl;
    out_ << "Email" << kTab << client.getEmail() << std::endl;

    out_ << std::endl << "Is it right?" << std::endl;
    out_ << "(Y)es, (E)dit, (C)ancel: ";

    std::string input;
    in_ >> input;

    if (input.empty()) {
      out_ << std::endl << "Wrong input. Try again." << std::endl;
    }

    char program = std::tolower(input[0]);

    switch (program) {
      case yesChar:
        repo_.save(std::move(client));
        out_ << std::endl << "Client added." << std::endl;
        return;

      case editChar:
        utils::PrintDelimiter(out_);
        client = readClientDetails();
        break;

      case cancelChar:
        out_ << std::endl << "You left adding new client." << std::endl;
        return;

      default:
        out_ << std::endl << "Wrong input. Try again." << std::endl;
    }
  }
}

Client ClientAddingDialog::readClientDetails() {
  std::string name;
  std::string email;

  out_ << "Write the name: ";
  while (name.empty()) {
    std::getline(in_, name);
  }

  out_ << "Write the email: ";
  while (email.empty()) {
    in_ >> email;
  }

  return Client(std::move(name), std::move(email));
}
