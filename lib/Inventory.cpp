#include "Inventory.hpp"
#include <iostream>

namespace mobicraft {
    // ctor
    Inventory::Inventory() : isCraftable(false){
        this->Inven = new Item*[27];
        for (int i = 0; i < 27; i++) this->Inven[i] = nullptr;
        this->Crinv = new Item*[9];
        for (int i = 0; i < 9; i++) this->Crinv[i] = nullptr;
    }

    // dtor
    Inventory::~Inventory() {
        delete[] this->Inven;
        delete[] this->Crinv;
    }

    // Command Handler
    std::istream& operator>>(std::istream& is, Inventory& I) {
        return is;
    }

    void Inventory::DeleteSlotContents(Stype s, int i) {
        if (s == Inv) {
            delete this->Inven[i];
            this->Inven[i] = nullptr;
        } else if (s == Cr) {
            delete this->Crinv[i];
            this->Crinv[i] = nullptr;
        }
    }

    // Methods
    void Inventory::compareCrinvRecipe(Config& config){
        Grid<std::string> CrinvOfItemName(3,3);

        int crinvIterator = 0;
        std::string nameAtCrinvIterator = "";

        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                if (this->Crinv[crinvIterator]){
                    nameAtCrinvIterator = Crinv[crinvIterator]->getName();
                    CrinvOfItemName.pushBackElmt(nameAtCrinvIterator);
                } else {
                    CrinvOfItemName.pushBackElmt("-");
                }
                ++crinvIterator;
            }
        }

        auto recipeList = config.getRecipes();
        for (const auto& recipe : recipeList){
            if (*recipe == CrinvOfItemName){
                isCraftable = true;
            }
        }
    }

    void Inventory::makeCrinvEmpty(){
        for (int i = 0; i < 9; ++i){
            this->DeleteSlotContents(Cr, i);
        }
    }

    const int Inventory::getMinimum() {
        for (int i = 0; i < 27; i++) {
            if (this->Inven[i] == nullptr) return i;
        }
        return -1;
    } // Gets ItemPTR of minimum empty slot

    const void Inventory::Show() {
        // Crafting
        for (int i = 0; i < 9; i++) {
            std::cout << "[ ";
            if (this->Crinv[i] != nullptr) {
                this->Crinv[i]->what();
            } else {
                std::cout << "Empty";
            }
            std::cout << " ]";
            if (i % 3 == 2) std::cout << std::endl;
            else std::cout << " ";
        }
        std::cout << std::endl;
        // Inventory
        for (int i = 0; i < 27; i++) {
            std::cout << "[ ";
            if (this->Inven[i] != nullptr) {
                this->Inven[i]->what();
            } else {
                std::cout << "Empty";
            }
            std::cout << " ]";
            if (i % 9 == 8) std::cout << std::endl;
            else std::cout << " ";
        }
    } // Menampilkan Isi Inven dan Crafting

    void Inventory::Give(Config& c, std::string s, int i) {
        std::map<std::string, Recipe *>::iterator it = c.recipesMap.find(s);
        if (it == c.recipesMap.end()) throw new NotExistsException();
        Recipe *r = c.recipesMap.at(s);
        if (r->isTool()) this->Inven[this->getMinimum()] = new Tool(r->id, r->name, r->type);
        else this->Inven[this->getMinimum()] = new NonTool(r->id, r->name, r->type, i);
    } // Menambahkan Item pada Inventory

    void Inventory::Discard(int i, int n) {
        if (this->Inven[i] == nullptr) throw new NothingSlotException();
        if (this->Inven[i]->isTool()) {
            this->DeleteSlotContents(Inv, i);
        } else {
            if (this->Inven[i]->getAmt() > n) {
                this->Inven[i]->setAmt(this->Inven[i]->getAmt() - n);
            } else if (this->Inven[i]->getAmt() == n) {
                this->DeleteSlotContents(Inv, i);
            } else {
                throw new NumberTooBigException();
            }
        }
    } // Membuang Item pada Inventory

    void Inventory::Move(Stype src, int i, int n, Stype dst, int* j) {
        std::cout << "Not Implemented" << std::endl;
        // Belum Bisa Implement, Tool gaada getter setter
    } // Generic Handler for Move command

    void Inventory::Use(int i) {
        if (!this->Inven[i]->isTool()) throw new WrongTypeException();
        if (this->Inven[i]->getAmt() > 0) this->Inven[i]->use();
        else this->DeleteSlotContents(Inv, i);
    } // Use dari inventory

    void Inventory::Craft() {

    } // Melakukan Crafting

    void Inventory::Import() {
        std::cout << "Not Implemented" << std::endl;
        // Belum Bisa Implement, Tool gaada getter setter
    } // Import Inventory dari file .txt

    const void Inventory::Export(std::string) {
        std::cout << "Not Implemented" << std::endl;
        // Belum Bisa Implement, Tool gaada getter setter
    } // Melakukan export pada file .txt
}
