#include "repositories/OrderRepository.h"

#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include "file-services/ConfigurationService.h"
#include "file-services/CsvFileService.h"
#include "models/Order.h"
#include "models/Product.h"
#include "models/Property.h"
#include "repositories/ClientRepository.h"
#include "repositories/ProductsRepository.h"
#include "utils/Utils.h"

namespace {

void Write(const Order& order, const CsvFileService& csv_file_service,
           ProductsRepository& products_repo) {
  Property id("id", {std::to_string(order.getId())});
  Property clientId("client_id", {std::to_string(order.getClient().getId())});

  csv_file_service.write({id, clientId});

  products_repo.save(order.getProducts(), order.getId());
}

std::vector<Order> ReadAll(const CsvFileService& csv_file_service,
                           const ClientRepository& client_repo,
                           const ProductsRepository& products_repo) {
  const std::vector<Property> data = csv_file_service.getAllLines();

  if (data.empty()) return {};

  const auto& ids = utils::FindColumn("id", data).getValues();
  const auto& client_ids = utils::FindColumn("client_id", data).getValues();

  return std::views::zip(ids, client_ids) |
         std::views::transform([&client_repo, &products_repo](auto row) {
           auto [id_str, client_id] = row;
           int id = utils::MapStringToInt(id_str);

           Client client = client_repo.getById(utils::MapStringToInt(client_id))
                               .value_or(Client{});
           std::vector<Product> products = products_repo.getForOrderId(id);

           return Order{id, client, products};
         }) |
         std::ranges::to<std::vector>();
}

}  // namespace

OrderRepository::OrderRepository(CsvFileService& csv_file_service,
                                 ClientRepository& client_repo,
                                 ProductsRepository& products_repo,
                                 ConfigurationService& config_service)
    : orders_(ReadAll(csv_file_service, client_repo, products_repo)),
      csv_file_service_(csv_file_service),
      client_repo_(client_repo),
      products_repo_(products_repo),
      config_service_(config_service) {}

std::vector<Order>& OrderRepository::getAll() { return orders_; }

const std::vector<Order>& OrderRepository::getAll() const { return orders_; }

OrderRepository::OrderId OrderRepository::save(Order order) {
  const OrderId id =
      order.getId() == -1 ? config_service_.getNextId() : order.getId();
  order.setId(id);

  const Order& stored = orders_.emplace_back(std::move(order));

  Write(stored, csv_file_service_, products_repo_);

  return id;
}
