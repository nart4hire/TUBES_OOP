#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

namespace mobicraft {
    class Item
    {
    protected:
        int id;
        std::string name;
        std::string type;
        int quantity;
    public:
        Item(int id, std::string name, std::string type, int quantity);
        ~Item();

        std::string getName() const;
        virtual void use() = 0;
        virtual void getinfo();
        virtual void what(); // Displays Item_Name Qty/Dur
    };
}
#endif