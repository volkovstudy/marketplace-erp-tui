#include "models/Client.h"

#include <string>
#include <string_view>

Client::Client(std::string_view full_name, std::string_view email)
    : full_name_(full_name), email_(email) {}

Client::Client(int id, std::string_view full_name, std::string_view email)
    : id_(id), full_name_(full_name), email_(email) {}

int Client::getId() const { return id_; }

void Client::setId(int id) { id_ = id; }

const std::string& Client::getFullName() const { return full_name_; }

void Client::setFullName(std::string_view full_name) { full_name_ = full_name; }

const std::string& Client::getEmail() const { return email_; }

void Client::setEmail(std::string_view email) { email_ = email; }
