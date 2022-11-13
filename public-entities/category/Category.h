#ifndef MARKETPLACE_ERP_TUI_CATEGORY_H
#define MARKETPLACE_ERP_TUI_CATEGORY_H


#include <string>

using namespace std;

class Category {
private:
    int id;
    string name;
public:
   explicit Category(string name);

    int getId() const;
    void setId(int id);

    const string &getName() const;
    void setName(const string &name);
};


#endif
