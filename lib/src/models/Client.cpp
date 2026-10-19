#include "models/Client.h"

#include <string>

Client::Client(const std::string& full_name, const std::string& email)
    : full_name_(full_name), email_(email) {}

Client::Client(int id, const std::string& full_name, const std::string& email)
    : id_(id), full_name_(full_name), email_(email) {}

int Client::getId() const { return id_; }

void Client::setId(int id) { id_ = id; }

const std::string& Client::getFullName() const { return full_name_; }

void Client::setFullName(const std::string& full_name) {
  full_name_ = full_name;
}

const std::string& Client::getEmail() const { return email_; }

void Client::setEmail(const std::string& email) { email_ = email; }
