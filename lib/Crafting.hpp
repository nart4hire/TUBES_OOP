#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#include "Config.hpp"
#include "Inventory.hpp"

namespace mobicraft
{
    class Crafting{
        private:
            Item* craftedItem;

            // Minimum quantity being used for each Crinv's item when crafting item 
            int minQtyUsed;

            Config& config;
            Inventory& inventory;

            // I.S: crinvConfig only contains tools item name
            // F.S: Return true if crinvConfig only contains two same tools name
            bool isOnlyTwoSameTools(Grid<Item *>& crinvConfig) const; 

            // I.S: this->craftedItem exists
            // F.S: - craftedItem moved to Inven 
            //      - some or all items in Crinv removed
            //      - this->craftedItem is deleted
            void moveCraftedItemToInven(int& quantity);

        public:
            Crafting(Config& c, Inventory& i);
            ~Crafting();

            // I.S: Crinven is not empty
            // F.S: if crafting is successful, move the craftedItem to Inven 
            void crafting();
            
    };
};

#endif