#include "Item.hpp"
#include <iostream>

namespace mobicraft {
    Item::Item(int id, std::string name, std::string type, int quantity) {
        this->id = id;
        this->name = name;
        this->type = type;
        this->quantity = quantity;
    }

    Item::~Item() {}

    void Item::getinfo() {
        std::cout << id << name << type << quantity;
    }

    void Item::what() {
        std::cout << name;
    }

    std::string Item::getName() const{
        return this->name;
    }
}