#include "Client.h"

#include <utility>

int CLIENT_AMOUNT;

Client::Client(string fullName, string email) :
        fullName(std::move(fullName)),
        email(std::move(email)) {
    Client::id = ++CLIENT_AMOUNT;
}

Client::Client(int id, string fullName, string email) : id(id), fullName(std::move(fullName)),
                                                        email(std::move(email)) {}

int Client::getId() const {
    return id;
}

void Client::setId(int id) {
    Client::id = id;
}

const string& Client::getFullName() const {
    return fullName;
}

void Client::setFullName(const string& fullName) {
    Client::fullName = fullName;
}

const string& Client::getEmail() const {
    return email;
}

void Client::setEmail(const string& email) {
    Client::email = email;
}
