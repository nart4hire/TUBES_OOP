#include "Tool.hpp"
#include <iostream>

namespace mobicraft {
    Tool::Tool(int id, std::string name, std::string type, int quantity) : Item(id, name, type, quantity) {
        this->durability = 10;
    }

    Tool::Tool(int id, std::string name, std::string type, int quantity, int durability) : Item(id, name, type, quantity) {
        this->durability = durability;
    }

    Tool::~Tool() {

    }

    void Tool::use() {
        if (this->durability != 1) {
            this->durability--;
        } else {
            this->~Tool();
        }
        
    }

    void Tool::getinfo() {
        std::cout << durability;
        Item::getinfo();
    }
}