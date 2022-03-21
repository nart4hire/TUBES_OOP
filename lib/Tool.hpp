#ifndef TOOL_HPP
#define TOOL_HPP

#include "Item.hpp"

namespace mobicraft {
    class Tool : public Item
    {
    private:
        int durability;
    public:
        Tool(int id, std::string name, std::string type, int quantity);
        Tool(int id, std::string name, std::string type, int quantity, int durability);
        ~Tool();
        
        void use();
        void getinfo();
    };
}
#endif