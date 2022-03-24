#include "Crafting.hpp"
#include "Inventory.hpp"

namespace mobicraft{
    Crafting::Crafting(Config& c, Inventory& i) : craftedItem(nullptr), config(c), inventory(i){        
    }

    Crafting::~Crafting(){
        delete craftedItem;
    }

    void Crafting::crafting(){
        // F.S: If craftedItem exists, move the craftedItem to Inven
        
        // Add each item's name in Crinv to crinvConfig
        Grid<std::string> crinvConfig(3,3);
        std::string itemName;

        for (int i = 0; i < 9; ++i){
            if (this->inventory.getCrinv(i)){
                itemName = this->inventory.getCrinv(i)->getName();
                crinvConfig.pushBackElmt(itemName);
            } else {
                crinvConfig.pushBackElmt("-");
            }
        }

        // Iterate on recipeList whether there is recipe's configuration which satisfies crinvConfig
        auto recipeList = this->config.getRecipes();
        int craftedItemQty = 0;
        
        for (const auto& recipe : recipeList){
            if (*recipe == crinvConfig && recipe->isRecipeTool()){
                craftedItemQty = 1;
                if (this->isOnlyTwoSameTools(crinvConfig)){    
                    this->craftedItem = new Tool(
                                            recipe->id, recipe->name, recipe->type, 
                                            this->inventory.sumCrinvToolsDurability()
                                            );
                    

                } else {
                    this->craftedItem = new Tool(recipe->id, recipe->name, recipe->type);
                }

                break;
            }

            else if (*recipe == crinvConfig && !recipe->isRecipeTool()){
                craftedItemQty = recipe->getAmt() * this->inventory.getMinQtyInCrinv();
                this->craftedItem = new NonTool(recipe->id, recipe->name, recipe->type, craftedItemQty);
                break;
            }
        }
        
        this->moveCraftedItemToInven(craftedItemQty);
    }

    void Crafting::moveCraftedItemToInven(int& quantity){
        // I.S: this->craftedItem exists
        // F.S: 
        //  - craftedItem moved to Inven 
        //  - this->craftedItem is deleted

        if (this->craftedItem){
            // Remove each item in Crinven as much as min quantity of items in Crinven 
            int minQty = this->inventory.getMinQtyInCrinv();

            for (int i = 0; i < 9; ++i){
                if (this->inventory.getCrinv(i) && this->inventory.getCrinv(i)->isTool()){
                    this->inventory.DeleteSlotContents(this->inventory.Cr, i);
                } else if (this->inventory.getCrinv(i) && !this->inventory.getCrinv(i)->isTool()) {
                    int remainingQty = this->inventory.getCrinv(i)->getAmt() - minQty;
                    if (remainingQty <= 0){
                        this->inventory.DeleteSlotContents(this->inventory.Cr, i);
                    } else {
                        this->inventory.getCrinv(i)->setAmt(remainingQty);
                    }
                }
            }
            
            // Move the crafted item to inventory
            inventory.Give(this->config, this->craftedItem->getName(), quantity);

            // <Inven full exception>

            delete this->craftedItem;
            this->craftedItem = nullptr;
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