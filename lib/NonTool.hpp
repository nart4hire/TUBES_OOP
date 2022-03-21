#ifndef NONTOOL_HPP
#define NONTOOL_HPP

#include "Item.hpp"

namespace mobicraft {
    class NonTool : public Item
    {
    private:
        /* data */
    public:
        NonTool(int id, std::string name, std::string type, int quantity);
        ~NonTool();

        void use();
        void getinfo();
    };
}
#endif