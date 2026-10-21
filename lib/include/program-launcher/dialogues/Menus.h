#pragma once

#include <utils/Utils.h>

#include <array>
#include <cstddef>
#include <optional>
#include <ostream>
#include <print>
#include <ranges>
#include <string_view>

namespace menus {

template <typename Action>
struct MenuOption {
  char key;
  std::string_view label;
  Action action;
};

template <typename Action, std::size_t N>
using Menu = std::array<MenuOption<Action>, N>;

template <typename Action, std::size_t N>
constexpr std::optional<Action> ParseChoice(const Menu<Action, N>& menu,
                                            std::string_view input) {
  if (input.size() != 1) return std::nullopt;

  const auto it = std::ranges::find(menu, utils::ToLowerCase(input.front()),
                                    &MenuOption<Action>::key);

  if (it == menu.end()) return std::nullopt;

  return it->action;
}

template <typename Action, std::size_t N>
std::optional<Action> ReadChoice(std::ostream& out, std::istream& in,
                                 const Menu<Action, N>& menu) {
  std::string input;

  while (true) {
    std::print(out, "\nYour choice (");
    for (auto [idx, option] : std::views::enumerate(menu)) {
      std::print(out, "{}{}", idx == 0 ? "" : ", ",
                 utils::ToUpperCase(option.key));
    }
    std::print(out, "): ");
    out.flush();

    if (!std::getline(in, input)) return std::nullopt;

    if (input.empty()) {
      std::println(out, "\nWrong input. Try again.");
      continue;
    }

    if (const auto action = ParseChoice(menu, input)) return action;

    std::println(out, "\nWrong input. Try again.");
  }
}

template <typename Action, std::size_t N>
void PrintMenu(std::ostream& out, const Menu<Action, N>& menu) {
  std::println(out, "What do you want to do?\n");

  for (const auto& option : menu) {
    std::println(out, "{};", option.label);
  }
}

}  // namespace menus
