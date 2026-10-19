#pragma once

#include <string>
#include <string_view>

class Client {
 public:
  Client() = default;
  Client(std::string_view full_name, std::string_view email);
  Client(int id, std::string_view full_name, std::string_view email);

  int getId() const;
  void setId(int id);

  const std::string& getFullName() const;
  void setFullName(std::string_view full_name);

  const std::string& getEmail() const;
  void setEmail(std::string_view email);

 private:
  int id_ = -1;
  std::string full_name_{};
  std::string email_{};
};
