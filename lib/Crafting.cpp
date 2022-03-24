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
        
        int idx = 0;
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                if (this->inventory.getCrinv(idx)){
                    if (this->inventory.getCrinv(idx)->hasType()){
                        crinvConfig.at(i,j) = this->inventory.getCrinv(idx)->getType();
                    } else {
                        crinvConfig.at(i,j) = this->inventory.getCrinv(idx)->getName();
                    }

                } else {
                    crinvConfig.at(i,j) = "-";
                }
                
                ++idx;
            }
        }

        if (crinvConfig.isNull()) {
            throw new NothingSlotException();

        } else {
            // Crafting item by evaluating Crinv configuration over one of recipe
            auto recipeList = this->config.getRecipes();
            int itemCraftedQty = 0;

            for (const auto& recipe : recipeList){
                if (*recipe == crinvConfig){
                    this->minQtyUsed = this->inventory.getMinQtyInCrinv();

                    if (recipe->isTool){
                        if (this->isOnlyTwoSameTools(crinvConfig)){    
                            this->craftedItem = new Tool(
                                                    recipe->id, recipe->name, recipe->type, 
                                                    this->inventory.sumCrinvToolsDurability());                                               
                        } else {
                            this->craftedItem = new Tool(recipe->id, recipe->name, recipe->type);
                        }

                        itemCraftedQty = 1;
                    
                    } else {
                        itemCraftedQty = recipe->getAmt() * minQtyUsed;
                        this->craftedItem = new NonTool(recipe->id, recipe->name, recipe->type, itemCraftedQty);
                    }

                    break;
                }
            }
            
            this->moveCraftedItemToInven(itemCraftedQty);
        }
    }

    void Crafting::moveCraftedItemToInven(int& quantity){
        // I.S: this->craftedItem exists
        // F.S: 
        //  - craftedItem moved to Inven and deleted if there is slot available; Otherwise, do nothing

        if (!this->craftedItem){
            throw new CraftedItemNotFound();

        } else {
            // Move the crafted item to inventory
            inventory.Give(this->config, this->craftedItem->getName(), quantity); // Exception is possibly thrown
            
            // Remove each item in Crinven as much as min quantity of items in Crinven 
            for (int i = 0; i < 9; ++i){
                if (this->inventory.getCrinv(i)){
                    if (this->inventory.getCrinv(i)->isTool()){
                        this->inventory.DeleteSlotContents(this->inventory.Cr, i);
                    } else {
                        int remainingQty = this->inventory.getCrinv(i)->getAmt() - this->minQtyUsed;
                        if (remainingQty == 0){
                            this->inventory.DeleteSlotContents(this->inventory.Cr, i);
                        } else {
                            this->inventory.getCrinv(i)->setAmt(remainingQty);
                        }
                    }
                }
            }

            this->minQtyUsed = 0;
            delete this->craftedItem;
            this->craftedItem = nullptr;
        }
    }

    bool Crafting::isOnlyTwoSameTools(Grid<std::string>& crinvConfig) const{
        // I.S: crinvConfig only contains tools item name
        // F.S: Return true if crinvConfig only contains two same tools name

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