#ifndef TOOL_HPP
#define TOOL_HPP

#include "Item.hpp"

namespace mobicraft {
    class Tool : public Item
    {
    private:
        int durability;
    public:
        Tool(int id, std::string name, std::string type);
        Tool(int id, std::string name, std::string type, int durability);
        ~Tool();

        void use();
        void getinfo();
        void what(); // Displays Item_Name Qty/Dur
    };
}
#endif