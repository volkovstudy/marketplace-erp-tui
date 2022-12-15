#ifndef MARKETPLACE_ERP_TUI_CLIENT_H
#define MARKETPLACE_ERP_TUI_CLIENT_H

#include <string>

using namespace std;

class Client {
private:
    int id;
    string fullName;
    string address;
    string email;
public:
    Client(string fullName, string address, string email);

    Client(int id, string fullName, string address, string email);

    int getId() const;
    void setId(int id);

    const string &getFullName() const;
    void setFullName(const string &fullName);

    const string &getAddress() const;
    void setAddress(const string &address);

    const string &getEmail() const;
    void setEmail(const string &email);
};


#endif
