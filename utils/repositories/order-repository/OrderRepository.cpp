#include "OrderRepository.h"

#include <utility>

OrderRepository::OrderRepository(string filePath, ClientRepository *clientRepository)
        : clientRepository(clientRepository) {
    csvFileService = new CsvFileService(std::move(filePath));
}
