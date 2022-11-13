#include "Category.h"

#include <utility>

int CATEGORY_COUNT;

Category::Category(string name) : name(std::move(name)) {
    id = ++CATEGORY_COUNT;
}

int Category::getId() const {
    return id;
}

void Category::setId(int id) {
    Category::id = id;
}

const string &Category::getName() const {
    return name;
}

void Category::setName(const string &name) {
    Category::name = name;
}
