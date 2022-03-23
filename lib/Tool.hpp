#ifndef TOOL_HPP
#define TOOL_HPP

#include "Item.hpp"

namespace mobicraft {
    class Tool : public Item
    {
    private:
        int durability;
    public:
        static const int MaxDurability = 10;

        Tool(int id, std::string name, std::string type);
        Tool(int id, std::string name, std::string type, int durability);
        ~Tool();

        void use();
        int getAmt();
        void setAmt(int);
        void getinfo();
        bool isTool();
        bool isFull();
        void what(std::ostream& os) const; // Displays Item_Name Qty/Dur
    };
}
#endif