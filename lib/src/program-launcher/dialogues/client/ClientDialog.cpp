#include "program-launcher/dialogues/client/ClientDialog.h"

#include <cstdint>
#include <istream>
#include <ostream>
#include <print>
#include <string>
#include <vector>

#include "program-launcher/dialogues/Menus.h"
#include "program-launcher/dialogues/client/ClientAddingDialog.h"
#include "table-printer/TablePrinter.h"

namespace {

enum class SectionAction : std::uint8_t { AddNew, ListAll, Quit };

constexpr menus::Menu<SectionAction, 3> kSectionMenu{
    {{'a', "(A)dd new client", SectionAction::AddNew},
     {'l', "(L)ist all clients", SectionAction::ListAll},
     {'q', "(Q)uit from the section", SectionAction::Quit}}};

enum class ListAction : std::uint8_t { Quit };

constexpr menus::Menu<ListAction, 1> kListMenu{
    {{'q', "(Q)uit from the section", ListAction::Quit}}};

}  // namespace

ClientDialog::ClientDialog(std::ostream& out, std::istream& in,
                           ClientRepository& repo)
    : out_(out), in_(in), repo_(repo) {}

void ClientDialog::openManagement() {
  std::print(out_, "You opened clients management section. ");

  while (true) {
    menus::PrintMenu(out_, kSectionMenu);

    switch (menus::ReadChoice(out_, in_, kSectionMenu)
                .value_or(SectionAction::Quit)) {
      using enum SectionAction;

      case AddNew:
        utils::PrintDelimiter(out_);
        addNewClient();
        break;

      case ListAll:
        utils::PrintDelimiter(out_);
        listAllClients();
        break;

      case Quit:
        std::println(out_, "\nYou left clients management section.");
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
  std::println(out_, "");

  menus::PrintMenu(out_, kListMenu);

  menus::ReadChoice(out_, in_, kListMenu);
}
