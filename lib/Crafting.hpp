#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#include "Config.hpp"

namespace mobicraft
{
    class Crafting{
        private:
            Item* craftedItem;

        public:
            Crafting();
            ~Crafting();

            Item& crafting(Config& config, Inventory& inventory); // Check whether Crinv satisfies one of recipe configuration
            void takeCraftedItem(Config& config, Inventory& inventory);
            int getMinimumQtyInCrinv(Inventory& inventory) const;
            int sumTwoToolsDurability(Inventory& inventory) const;
            bool isTwoSameTools(Grid<std::string>& crinvConfig) const;
    };
};

#endif