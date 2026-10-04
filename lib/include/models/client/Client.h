#pragma once

#include <string>

using namespace std;

class Client {
 public:
  Client(string fullName, string email);
  Client(int id, string fullName, string email);

  int getId() const;
  void setId(int id);

  const string& getFullName() const;
  void setFullName(const string& fullName);

  const string& getEmail() const;
  void setEmail(const string& email);

 private:
  int id;
  string fullName;
  string email;
};
