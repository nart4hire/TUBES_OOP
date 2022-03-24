#include "Tool.hpp"
#include <iostream>

namespace mobicraft {
    Tool::Tool(int id, std::string name, std::string type)
            : Item(id, name, type), durability(MaxDurability) {}

    Tool::Tool(int id, std::string name, std::string type, int durability)
            : Item(id, name, type), durability(durability) {}

    Tool::~Tool() {}

    void Tool::use() {
        this->durability--;
        std::cout << "Using " << this->name << "." << std::endl;
        if (this->durability == 0) {
            std::cout << "The tool " << this->name << " broke." << std::endl;
        }
    }

    void Tool::getinfo() {
        std::cout << durability;
        Item::getinfo();
    }

    int Tool::getAmt() {
        return this->durability;
    }

    void Tool::setAmt(int x) {
        this->durability = x;
    }

    bool Tool::isTool() {
        return true;
    }

    bool Tool::isFull() {
        return (this->durability == MaxDurability);
    }

    void Tool::what(std::ostream& os) const {
        this->Item::what(os);
        os << " " << this->durability;
    }
}