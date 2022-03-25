#include "Item.hpp"
#include <iostream>

namespace mobicraft {
    Item::Item(int id, std::string name, std::string type)
        : id(id), name(name), type(type)
    {
    }

    Item::Item(Item& I) : id(I.id), name(I.name), type(I.type) {}

    Item::~Item() {}

    void Item::getinfo() {
        std::cout << id << name << type;
    }

    bool Item::operator==(const Item& dst) {
        return (this->id == dst.id && this->name == dst.name && this->type == dst.type);
    }

    bool operator==(const Item *item, const std::string& str) {
        return item->name == str || item->type == str;
    }

    bool operator!=(const Item *item, const std::string& str) {
        return !(item == str);
    }

    bool Item::equals(const Item& dst) {
        return (this->id == dst.id && this->name == dst.name && this->type == dst.type);
    }

    void Item::what(std::ostream& os) const {
        os << this->name;
    }

    std::ostream& operator<<(std::ostream& os, const Item* item)
    {
        item->what(os);
        return os;
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