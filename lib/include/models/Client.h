#pragma once

#include <string>

class Client {
 public:
  Client(std::string fullName, std::string email);
  Client(int id, std::string fullName, std::string email);

  int getId() const;
  void setId(int id);

  const std::string& getFullName() const;
  void setFullName(const std::string& fullName);

  const std::string& getEmail() const;
  void setEmail(const std::string& email);

 private:
  int id;
  std::string fullName;
  std::string email;
};
