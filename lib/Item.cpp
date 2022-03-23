#include "Item.hpp"
#include <iostream>

namespace mobicraft {
    Item::Item(int id, std::string name, std::string type)
        : id(id), name(name), type(type)
    {
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

    const int Item::getId() const {
        return this->id;
    }

    const std::string& Item::getName() const{
        return this->name;
    }

    const std::string& Item::getType() const{
        return this->type;
    }

    bool Item::hasType() const {
        return this->type != "-";
    }
}