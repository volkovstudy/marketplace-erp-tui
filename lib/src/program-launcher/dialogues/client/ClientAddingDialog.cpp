#include "program-launcher/dialogues/client/ClientAddingDialog.h"

#include <iostream>
#include <string>

#include "models/Client.h"
#include "repositories/ClientRepository.h"
#include "utils/Utils.h"

#define pathToClientsFile "marketplace-erp/clients.csv"

#define tab "\t"

#define yesChar "y"
#define editChar "e"
#define cancelChar "c"

void getInformationAboutClient(std::string& name, std::string& email);
void saveClient(Client client);

void ClientAddingDialog::addClient() {
  std::cout << "Now you're going to add new client." << std::endl;

  std::string name, email;
  getInformationAboutClient(name, email);

  do {
    Utils::printDelimiter();

    std::cout << "Well, check the information about new client:" << std::endl;
    std::cout << "Name" << tab << name << std::endl;
    std::cout << "Email" << tab << email << std::endl;

    std::cout << std::endl << "Is it right?" << std::endl;
    std::cout << "(Y)es, (E)dit, (C)ancel: ";

    std::string program;
    std::cin >> program;
    Utils::toLowerCase(&program);

    if (program == yesChar) {
      Client client(name, email);
      saveClient(client);

      std::cout << std::endl << "Client added." << std::endl;

      break;
    } else if (program == editChar) {
      Utils::printDelimiter();
      getInformationAboutClient(name, email);
    } else if (program == cancelChar) {
      std::cout << std::endl << "You left adding new client." << std::endl;
      return;
    } else {
      std::cout << std::endl << "Wrong input. Try again." << std::endl;
    }
  } while (true);
}

void getInformationAboutClient(std::string& name, std::string& email) {
  std::cout << "Write the name: ";
  do {
    std::getline(std::cin, name);
  } while (name.empty());

  std::cout << "Write the email: ";
  do {
    std::cin >> email;
  } while (email.empty());
}

void saveClient(Client client) {
  ClientRepository clientRepository(pathToClientsFile);

  clientRepository.save(&client);
}
