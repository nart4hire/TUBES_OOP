#ifndef NONTOOL_HPP
#define NONTOOL_HPP

#include "Item.hpp"

namespace mobicraft {
    class NonTool : public Item
    {
    private:
        int quantity;
    public:
        static const int MaxQuantity = 64;

        NonTool(int id, std::string name, std::string type, int quantity);
        ~NonTool();

        void use();
        int getAmt();
        void setAmt(int);
        void getinfo();
        bool isTool();
        bool isFull();
        void what(); // Displays Item_Name Qty/Dur
    };
}
#endif