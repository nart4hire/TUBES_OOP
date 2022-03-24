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

            // If exists, return crafted item by inventory.Crinv
            Item& crafting(Config& config, Inventory& inventory);
            
            void moveCraftedItemToInven(Config& config, Inventory& inventory);

            int getMinimumQtyInCrinv(Inventory& inventory) const;
            
            // Return true if crinvConfig only consists of two same tools
            bool isOnlyTwoSameTools(Grid<std::string>& crinvConfig) const; 

            int sumToolsDurability(Inventory& inventory) const;
    };
};

#endif