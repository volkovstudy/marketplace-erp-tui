#include "program-launcher/dialogues/client/ClientDialog.h"

#include <cctype>
#include <cstdint>
#include <istream>
#include <optional>
#include <ostream>
#include <print>
#include <string>
#include <string_view>
#include <vector>

#include "program-launcher/dialogues/client/ClientAddingDialog.h"
#include "repositories/ClientRepository.h"
#include "table-printer/TablePrinter.h"
#include "utils/Utils.h"

namespace {

constexpr char kAddNewClientChar = 'a';
constexpr char kListAllClientsChar = 'l';
constexpr char kQuitChar = 'q';

enum class UserChoice : std::uint8_t { AddNew, ListAll, Quit };

constexpr std::optional<UserChoice> ParseUserChoice(std::string_view input) {
  const auto command = static_cast<unsigned char>(std::tolower(input.front()));

  switch (command) {
    using enum UserChoice;

    case kAddNewClientChar:
      return AddNew;
    case kListAllClientsChar:
      return ListAll;
    case kQuitChar:
      return Quit;
    default:
      return std::nullopt;
  }
}

void PrintSectionVariants(std::ostream& out) {
  std::println(out, "What do you want to do?\n");

  std::println(out, "(A)dd new client;");
  std::println(out, "(L)ist all clients;");
  std::println(out, "(Q)uit from the section;");
}

}  // namespace

ClientDialog::ClientDialog(std::ostream& out, std::istream& in,
                           ClientRepository& repo)
    : out_(out), in_(in), repo_(repo) {}

void ClientDialog::openManagement() {
  std::print(out_, "You opened clients management section. ");

  while (true) {
    PrintSectionVariants(out_);

    if (bool does_user_want_to_quit = handleUserChoice()) {
      utils::PrintDelimiter(out_);
      return;
    }

    utils::PrintDelimiter(out_);

    std::println(out_, "You came back to the clients management section.");
  }
}

void ClientDialog::addNewClient() {
  ClientAddingDialog dialog(out_, in_, repo_);
  dialog.addClient();
}

void ClientDialog::listAllClients() {
  const std::vector<Client>& clients = repo_.getAll();

  if (clients.empty()) {
    std::println(out_, "There are no clients!");
    return;
  }

  std::println(out_, "All clients:");

  TablePrinter printer(out_);
  printer.print(clients);

  std::println(out_, "\nWhat do you want to do?");
  std::println(out_, "(Q)uit;");

  while (true) {
    std::print(out_, "\nYour choice (Q): ");

    std::string input;
    in_ >> input;

    if (input.empty()) {
      std::println(out_, "\nWrong input. Try again.");
      continue;
    }

    const auto choice = ParseUserChoice(input);

    if (!choice.has_value()) {
      std::println(out_, "\nWrong input. Try again.");
      continue;
    }

    if (choice.value() == UserChoice::Quit) {
      return;
    } else {
      std::println(out_, "\nWrong input. Try again.");
    }
  }
}

bool ClientDialog::handleUserChoice() {
  while (true) {
    std::print(out_, "\nYour choice (A, L, Q): ");

    std::string input;
    in_ >> input;

    if (input.empty()) {
      std::println(out_, "\nWrong input. Try again.");
      continue;
    }

    const auto choice = ParseUserChoice(input);

    if (!choice.has_value()) {
      std::println(out_, "\nWrong input. Try again.");
      continue;
    }

    switch (choice.value()) {
      using enum UserChoice;
      case AddNew:
        utils::PrintDelimiter(out_);
        addNewClient();
        return false;

      case ListAll:
        utils::PrintDelimiter(out_);
        listAllClients();
        return false;

      case Quit:
        std::println(out_, "\nYou left clients management section.");
        return true;
    }
  }
}
