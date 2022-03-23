#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "Exception.hpp"

namespace mobicraft {
    class Item
    {
    protected:
        const int id;
        const std::string name;
        const std::string type;
    public:
        Item(int id, std::string name, std::string type);
        ~Item();

        const int getId() const;
        const std::string& getName() const;
        const std::string& getType() const;
        bool hasType() const;

        bool operator==(const Item&);
        bool equals(const Item&);

        virtual void use() = 0;
        virtual int getAmt() = 0;
        virtual void setAmt(int) = 0;
        virtual bool isTool() = 0;
        virtual bool isFull() = 0;
        virtual void getinfo();
        virtual void what(); // Displays Item_Name Qty/Dur
    };
}
#endif