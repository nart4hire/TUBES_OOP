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

            // Minimum quantity used in crafting item for each Crinv's item
            int minQtyUsed;

            Config& config;
            Inventory& inventory;

            // I.S: crinvConfig only contains tools item name
            // F.S: Return true if crinvConfig only contains two same tools name
            bool isOnlyTwoSameTools(Grid<std::string>& crinvConfig) const; 

            // I.S: this->craftedItem exists
            // F.S: - craftedItem moved to Inven 
            //      - this->craftedItem is destructed
            void moveCraftedItemToInven(int& quantity);

        public:
            Crafting(Config& c, Inventory& i);
            ~Crafting();

            // F.S: craftedItem is successfully crafted or unsuccessful
            void crafting();
            
    };
};

#endif