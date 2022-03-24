#include "Crafting.hpp"
#include "Inventory.hpp"

namespace mobicraft{
    Crafting::Crafting(){
        craftedItem = nullptr;
    }

    Crafting::~Crafting(){
        delete craftedItem;
    }

    Item& Crafting::crafting(Config& config, Inventory& inventory){
        // If exist, return crafted item of inventory.Crinv
        
        // Add each item's name in Crinv to crinvConfig
        Grid<std::string> crinvConfig(3,3);
        std::string itemName;

        for (int i = 0; i < 9; ++i){
            if (inventory.getCrinv(i)){
                itemName = inventory.getCrinv(i)->getName();
                crinvConfig.pushBackElmt(itemName);
            } else {
                crinvConfig.pushBackElmt("-");
            }
        }

        // Iterate on recipeList whether there is recipe's configuration which satisfies crinvConfig
        auto recipeList = config.getRecipes();
        for (const auto& recipe : recipeList){
            if (*recipe == crinvConfig){
                if (recipe->isRecipeTool()){
                    if (this->isOnlyTwoSameTools(crinvConfig)){    
                        this->craftedItem = new Tool(
                                                recipe->id, recipe->name, recipe->type, 
                                                this->sumCrinvToolsDurability(inventory)
                                                );

                        return *craftedItem;

                    } else {
                        this->craftedItem = new Tool(recipe->id, recipe->name, recipe->type);
                        return *craftedItem;
                    }

                } else {
                    this->craftedItem = new NonTool(  
                                            recipe->id, recipe->name, recipe->type, 
                                            recipe->getAmt() * this->getMinQtyInCrinv(inventory)
                                            );
                    
                    return *craftedItem;
                }   
            }
        }
        return *craftedItem; // nullPtr
    }

    void Crafting::moveCraftedItemToInven(Config& config, Inventory& inventory){
        // I.S: this->craftedItem exists
        // F.S: this->craftedItem is destructed

        if (this->craftedItem){
            // Remove each item in Crinven as much as min quantity of items in Crinven 
            int minQty = this->getMinQtyInCrinv(inventory);

            for (int i = 0; i < 9; ++i){
                if (inventory.getCrinv(i)){
                    if (inventory.getCrinv(i)->isTool()){
                        inventory.setCrinv(i, nullptr);
                    } else {
                        int remainingQty = inventory.getCrinv(i)->getAmt() - minQty;
                        if (remainingQty <= 0){
                            inventory.setCrinv(i, nullptr);
                        } else {
                            inventory.getCrinv(i)->setAmt(remainingQty);
                        }
                    }
                }
            }
            
            // Move the crafted item to inventory
            inventory.Give(config, this->craftedItem->getName(), this->craftedItem->getAmt());
            this->~Crafting();
        }
    }

    int Crafting::getMinQtyInCrinv(Inventory& inventory) const{
        // Return the minimum quantity of all items in Crinv
        
        int min = 0;
        for (int i = 1; i < 9; ++i){
            if (inventory.getCrinv(i)){
                if (inventory.getCrinv(i)->isTool()){
                    return 1;
                } else {
                    if (inventory.getCrinv(i)->getAmt() < min){
                        min = inventory.getCrinv(i)->getAmt();
                    }
                }
            }
        }
        return min;
    }

    int Crafting::sumCrinvToolsDurability(Inventory& inventory) const{
        int sumDurability = 0;
        for (int i = 0; i < 9; ++i){
            if (inventory.getCrinv(i) && inventory.getCrinv(i)->isTool()){
                sumDurability += inventory.getCrinv(i)->getAmt();
            }
        }

        if (sumDurability <= 10){
           return sumDurability;    
        } else {
            return 10;
        }
    }

    bool Crafting::isOnlyTwoSameTools(Grid<std::string>& crinvConfig) const{
        // I.S: crinvConfig only contains tools item name
        // F.S: Return true if Crinv configuration only contains two same tools

        int rows = crinvConfig.rows();
        int cols = crinvConfig.cols();

        if (rows + cols != 2){
            return false;
        } else {
            if (crinvConfig.at(0, 0) != crinvConfig.at(rows-1, cols-1)){
                return false;
            }
        }

        return true;
    }
}