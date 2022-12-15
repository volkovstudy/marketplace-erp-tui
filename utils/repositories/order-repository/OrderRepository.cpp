#include "OrderRepository.h"

#include <utility>

OrderRepository::OrderRepository(string filePath, ClientRepository *clientRepository,
                                 ProductsRepository *productsRepository) :
        clientRepository(clientRepository),
        productsRepository(productsRepository) {
    csvFileService = new CsvFileService(std::move(filePath));
}

vector<Order *> OrderRepository::getAll() {
    if (!orders.empty()) return orders;

    vector<Order *> result;
    vector<Property *> allLines = csvFileService->getAllLines();

    int maxAmountOfLines = 0;
    for (Property *property: allLines) {
        int amountOfLines = (int) property->getValues().size();
        maxAmountOfLines = max(maxAmountOfLines, amountOfLines);
    }

    for (int i = 0; i < maxAmountOfLines; ++i) {
        int id = 0;
        Client *client;

        for (Property *property: allLines) {
            if (property->getValues().size() < maxAmountOfLines) break;

            string value = property->getValues().at(i);
            string fieldName = property->getFieldName();

            if (fieldName == "id")
                id = stoi(value);
            if (fieldName == "client_id")
                client = clientRepository->getById(stoi(value));
        }

        map<string, int> products = productsRepository->getForOrderId(id);

        auto *order = new Order(id, client, products);
        result.push_back(order);
    }

    orders = result;

    return orders;
}
