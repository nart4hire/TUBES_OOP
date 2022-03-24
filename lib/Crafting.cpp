#include "Crafting.hpp"
#include "Inventory.hpp"

namespace mobicraft{
    Crafting::Crafting(Config& c, Inventory& i) : craftedItem(nullptr), minQtyUsed(0), config(c), inventory(i){        
    }

    Crafting::~Crafting(){
        delete craftedItem;
    }

    void Crafting::crafting(){
        // F.S: craftedItem is successfully crafted or unsuccessful
        
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

        if (crinvConfig.isNull()) {
            throw new NothingSlotException();

        } else {
            // Iterate on recipeList whether there is recipe's configuration which satisfies crinvConfig
            auto recipeList = this->config.getRecipes();
            for (const auto& recipe : recipeList){
                if (*recipe == crinvConfig && recipe->isRecipeTool()){
                    this->minQtyUsed = this->inventory.getMinQtyInCrinv();

                    if (this->isOnlyTwoSameTools(crinvConfig)){    
                        this->craftedItem = new Tool(
                                                recipe->id, recipe->name, recipe->type, 
                                                this->inventory.sumCrinvToolsDurability()
                                                );
                    } else {
                        this->craftedItem = new Tool(recipe->id, recipe->name, recipe->type);
                    }
                    
                    break;

                } else if (*recipe == crinvConfig && !recipe->isRecipeTool()){
                    int craftedItemQty = recipe->getAmt() * minQtyUsed;
                    this->craftedItem = new NonTool(recipe->id, recipe->name, recipe->type, craftedItemQty);
                    break;
                }
            }
        }
    }

    void Crafting::moveCraftedItemToInven(){
        // I.S: this->craftedItem exists
        // F.S: 
        //  - craftedItem moved to Inven and deleted if there is slot available; Otherwise, do nothing

        if (!this->craftedItem){
            throw new CraftedItemIsNotFound();

        } else {
            // Move the crafted item to inventory
            int craftedItemQty = 0;
            
            if (craftedItem->isTool()){
                craftedItemQty = 1;
            } else {
                craftedItemQty = craftedItem->getAmt();
            }
            
            inventory.Give(this->config, this->craftedItem->getName(), craftedItemQty);

            // Remove each item in Crinven as much as min quantity of items in Crinven 
            for (int i = 0; i < 9; ++i){
                if (this->inventory.getCrinv(i) && this->inventory.getCrinv(i)->isTool()){
                    this->inventory.DeleteSlotContents(this->inventory.Cr, i);
                } else if (this->inventory.getCrinv(i) && !this->inventory.getCrinv(i)->isTool()) {
                    int remainingQty = this->inventory.getCrinv(i)->getAmt() - minQtyUsed;
                    if (remainingQty == 0){
                        this->inventory.DeleteSlotContents(this->inventory.Cr, i);
                    } else {
                        this->inventory.getCrinv(i)->setAmt(remainingQty);
                    }
                }
            }

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