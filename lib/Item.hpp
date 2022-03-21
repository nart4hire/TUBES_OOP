#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

namespace mobicraft {
    class Item
    {
    private:
        int id;
        std::string name;
        std::string type;
        int quantity;
    public:
        Item(int id, std::string name, std::string type, int quantity);
        ~Item();

        virtual void use() = 0;
        virtual void getinfo();
    };
}
#endif