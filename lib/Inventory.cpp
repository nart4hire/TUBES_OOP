#include "Inventory.hpp"
#include <iostream>

namespace mobicraft {
    // ctor
    Inventory::Inventory() {
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

    // Methods

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
        Recipe *r = c.recipesMap[s];
        if (r->isTool()) this->Inven[this->getMinimum()] = new Tool(r->id, r->name, r->type);
        else this->Inven[this->getMinimum()] = new NonTool(r->id, r->name, r->type, i);
    } // Menambahkan Item pada Inventory

    void Inventory::Discard(int i, int j) {
        std::cout << "Not Implemented" << std::endl;
        // Belum Bisa Implement, Tool gaada getter setter
    } // Membuang Item pada Inventory

    void Inventory::Move(Stype src, int i, int n, Stype dst, int* j) {
        std::cout << "Not Implemented" << std::endl;
        // Belum Bisa Implement, Tool gaada getter setter
    } // Generic Handler for Move command

    void Inventory::Use(int i) {
        try {
            this->Inven[i]->use();
        } // catch tool break/nullptr
    } // Use dari inventory

    void Inventory::Craft() {
        // Belum Diimplement
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
