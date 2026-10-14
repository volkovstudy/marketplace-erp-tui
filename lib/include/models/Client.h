#pragma once

#include <string>

class Client {
 public:
  Client() = default;
  Client(const std::string& full_name, const std::string& email);
  Client(int id, const std::string& full_name, const std::string& email);

  int getId() const;
  void setId(int id);

  const std::string& getFullName() const;
  void setFullName(const std::string& full_name);

  const std::string& getEmail() const;
  void setEmail(const std::string& email);

 private:
  int id_ = 0;
  std::string full_name_{};
  std::string email_{};
};
