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

            // If exists, return crafted item by inventory.Crinv; otherwise, return nullPtr
            Item& crafting(Config& config, Inventory& inventory);
            
            // I.S: this->craftedItem exists
            // F.S: craftedItem is destructed
            void moveCraftedItemToInven(Config& config, Inventory& inventory);

            // Return the minimum quantity of all items in Crinv
            int getMinQtyInCrinv(Inventory& inventory) const;
            
            // I.S: crinvConfig only contains tools item name
            // F.S: Return true if Crinv configuration only contains two same tools
            bool isOnlyTwoSameTools(Grid<std::string>& crinvConfig) const; 

            int sumCrinvToolsDurability(Inventory& inventory) const;
    };
};

#endif