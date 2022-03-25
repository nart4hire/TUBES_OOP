#include "Crafting.hpp"
#include "Inventory.hpp"

namespace mobicraft{
    Crafting::Crafting(Config& c, Inventory& i) : craftedItem(nullptr), minQtyUsed(0), config(c), inventory(i){        
    }

    Crafting::~Crafting(){
        delete craftedItem;
    }

    void Crafting::crafting(){
        // Convert Crinven container to grid of string. Used for comparing with recipes configuration
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
            throw NothingSlotException();

        } else { // Crafting item by evaluating Crinv configuration over recipes
            int itemCraftedQty = 0;

            auto recipeList = this->config.getRecipes();
            for (const auto& recipe : recipeList){
                if (recipe->isCraftable()){
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
            }
            
            this->moveCraftedItemToInven(itemCraftedQty);
        }
    }

    void Crafting::moveCraftedItemToInven(int& quantity){
        if (!this->craftedItem){
            throw CraftedItemNotFound();
        } else {
            inventory.Give(this->config, this->craftedItem->getName(), quantity); // Exception is possibly thrown
            
            // Remove some or all items in Crinven
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
        // I.S: crinvConfig only contains tools item
        // F.S: Return true if crinvConfig only contains two same tools type

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
