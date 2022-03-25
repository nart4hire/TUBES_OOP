#include "NonTool.hpp"
#include <iostream>

namespace mobicraft {
    NonTool::NonTool(int id, std::string name, std::string type, int quantity)
            : Item(id, name, type), quantity(quantity) {}

    NonTool::~NonTool() {}

    void NonTool::use() {
        std::cout << "nothing happened" << std::endl;
    }

    void NonTool::getinfo() {
        Item::getinfo();
    }

    int NonTool::getAmt() {
        return this->quantity;
    }

    void NonTool::setAmt(int x) {
        this->quantity = x;
    }

    bool NonTool::isTool() {
        return false;
    }

    bool NonTool::isFull() {
        return (this->quantity == MaxQuantity);
    }

    void NonTool::what(std::ostream& os) const {
        this->Item::what(os);
        os << " Q" << this->quantity;
    }
}