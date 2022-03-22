#include "Tool.hpp"
#include <iostream>

namespace mobicraft {
    Tool::Tool(int id, std::string name, std::string type) : Item(id, name, type, 1) {
        this->durability = 10;
    }

    Tool::Tool(int id, std::string name, std::string type, int durability) : Item(id, name, type, 1) {
        this->durability = durability;
    }

    Tool::~Tool() {

    }

    void Tool::use() {
        if (this->durability != 1) {
            this->durability--;
        } else {
            this->~Tool();
            std::cout << "The tool " << this->name << " broke." << std::endl;
        }
    }

    void Tool::getinfo() {
        std::cout << durability;
        Item::getinfo();
    }

    void Tool::what() {
        Item::what();
        std::cout << " " << this->durability;
    }
}