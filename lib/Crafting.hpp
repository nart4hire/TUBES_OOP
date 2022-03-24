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
            Config& config;
            Inventory& inventory;

        public:
            Crafting(Config& config, Inventory& inventory);
            ~Crafting();

            // F.S: If craftedItem exists, move the craftedItem to Inven
            void crafting();
            
            // I.S: this->craftedItem exists
            // F.S: 
            //  - craftedItem moved to Inven 
            //  - this->craftedItem is destructed
            void moveCraftedItemToInven(int& quantity);
            
            // I.S: crinvConfig only contains tools item name
            // F.S: Return true if Crinv configuration only contains two same tools
            bool isOnlyTwoSameTools(Grid<std::string>& crinvConfig) const; 
    };
};

#endif