#include "Item.hpp"
#include <iostream>

namespace mobicraft {
    Item::Item(int id, std::string name, std::string type) {
        this->id = id;
        this->name = name;
        this->type = type;
    }

    Item::~Item() {}

    void Item::getinfo() {
        std::cout << id << name << type;
    }

    bool Item::operator==(const Item& dst) {
        return (this->id == dst.id && this->name == dst.name && this->type == dst.type);
    }

    bool Item::equals(const Item& dst) {
        return (this->id == dst.id && this->name == dst.name && this->type == dst.type);
    }

    void Item::what() {
        std::cout << name;
    }

    std::string Item::getName() const{
        return this->name;
    }
}