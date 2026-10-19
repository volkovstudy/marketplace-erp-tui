#include "program-launcher/dialogues/client/ClientAddingDialog.h"

#include <cstdint>
#include <optional>
#include <print>
#include <string>
#include <string_view>
#include <utility>

#include "models/Client.h"
#include "repositories/ClientRepository.h"
#include "utils/Utils.h"

namespace {

constexpr char kTab = '\t';

constexpr char kYesChar = 'y';
constexpr char kEditChar = 'e';
constexpr char kCancelChar = 'c';

enum class UserChoice : std::uint8_t { Yes, Edit, Cancel };

constexpr std::optional<UserChoice> ParseUserChoice(std::string_view input) {
  const auto command = static_cast<unsigned char>(std::tolower(input.front()));

  switch (command) {
    using enum UserChoice;

    case kYesChar:
      return Yes;
    case kEditChar:
      return Edit;
    case kCancelChar:
      return Cancel;
    default:
      return std::nullopt;
  }
}

}  // namespace

ClientAddingDialog::ClientAddingDialog(std::ostream& out, std::istream& in,
                                       ClientRepository& repo)
    : out_(out), in_(in), repo_(repo) {}

void ClientAddingDialog::addClient() {
  std::print(out_, "Now you're going to add new client.\n");

  Client client = readClientDetails();

  while (true) {
    utils::PrintDelimiter(out_);

    std::println(out_, "Well, check the information about new client:");
    std::println(out_, "Name{}{}", kTab, client.getFullName());
    std::println(out_, "Email{}{}", kTab, client.getEmail());

    std::println(out_, "\nIs it right?");
    std::print(out_, "(Y)es, (E)dit, (C)ancel: ");

    std::string input;
    in_ >> input;

    if (input.empty()) {
      std::println(out_, "\nWrong input. Try again.");
      continue;
    }

    auto choice = ParseUserChoice(input);
    if (!choice.has_value()) {
      std::println(out_, "\nWrong input. Try again.");
      continue;
    }

    switch (choice.value()) {
      using enum UserChoice;
      case Yes:
        repo_.save(std::move(client));
        std::println(out_, "\nClient added.");
        return;

      case Edit:
        utils::PrintDelimiter(out_);
        client = readClientDetails();
        break;

      case Cancel:
        std::println(out_, "\nYou left adding new client.");
        return;
    }
  }
}

Client ClientAddingDialog::readClientDetails() {
  std::string name;
  std::print(out_, "Write the name: ");
  while (name.empty()) {
    std::getline(in_, name);
  }

  std::string email;
  std::print(out_, "Write the email: ");
  while (email.empty()) {
    in_ >> email;
  }

  return Client(std::move(name), std::move(email));
}
