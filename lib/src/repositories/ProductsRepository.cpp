#include "repositories/ProductsRepository.h"

#include <ranges>
#include <string>
#include <vector>

#include "file-services/CsvFileService.h"
#include "models/Order.h"
#include "models/Product.h"
#include "models/Property.h"
#include "utils/Utils.h"

ProductsRepository::ProductsRepository(CsvFileService& csv_file_service)
    : csv_file_service_(csv_file_service) {}

std::vector<Product> ProductsRepository::getForOrderId(int id) const {
  std::vector<Property> data = csv_file_service_.getAllLines();

  if (data.empty()) return {};

  const auto& order_ids = utils::FindColumn("order_id", data).getValues();
  const auto& names = utils::FindColumn("name", data).getValues();
  const auto& amounts = utils::FindColumn("amount", data).getValues();

  return std::views::zip(order_ids, names, amounts) |
         std::views::filter([&id](auto row) {
           auto [order_id, name, amount] = row;
           return utils::MapStringToInt(order_id) == id;
         }) |
         std::views::transform([](auto row) {
           auto [order_id, name, amount] = row;
           return Product{name, utils::MapStringToInt(amount)};
         }) |
         std::ranges::to<std::vector>();
}

void ProductsRepository::save(const std::vector<Product>& products,
                              int order_id) {
  std::string id_str = std::to_string(order_id);

  for (const auto& product : products) {
    Property name("name", {product.getName()});
    Property amount("amount", {std::to_string(product.getAmount())});
    Property orderIdProperty("order_id", {id_str});

    csv_file_service_.write({name, amount, orderIdProperty});
  }
}
