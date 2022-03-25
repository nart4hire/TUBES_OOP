#include "Inventory.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace mobicraft {
    // ctor
    Inventory::Inventory(){
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

    // Methods
    Item* Inventory::getInven(int idx){
        return Inven[idx];
    }

    void Inventory::setInven(int idx, Item* item){
        Inven[idx] = item;
    }

    Item* Inventory::getCrinv(int idx){
        return Crinv[idx];
    }

    void Inventory::setCrinv(int idx, Item* item){
        Crinv[idx] = item;
    }

    int Inventory::getMinQtyInCrinv() const{
        int min = 0;
        for (int i = 0; i < 9; ++i){
            if (Crinv[i] && Crinv[i]->isTool()){
                return 1;
            }
            else if (Crinv[i] && !Crinv[i]->isTool()){
                if (min == 0){
                    min = Crinv[i]->getAmt();
                }
                else if (min != 0 && Crinv[i]->getAmt() < min){
                    min = Crinv[i]->getAmt();
                }
            }
        }
        return min;
    }

    int Inventory::sumCrinvToolsDurability() const{
        int sumDurability = 0;
        for (int i = 0; i < 9; ++i){
            if (Crinv[i] && Crinv[i]->isTool()){
                sumDurability += Crinv[i]->getAmt();
            }
        }

        if (sumDurability <= 10){
           return sumDurability;
        } else {
            return 10;
        }
    }

    void Inventory::DeleteSlotContents(Stype s, int i) {
        if (s == Inv) {
            delete this->Inven[i];
            this->Inven[i] = nullptr;
        } else if (s == Cr) {
            delete this->Crinv[i];
            this->Crinv[i] = nullptr;
        }
    } // Auxiliary for deleting items in inventory slots


    const int Inventory::getMinimum() {
        for (int i = 0; i < 27; i++) {
            if (this->Inven[i] == nullptr) return i;
        }
        return -1;
    } // Gets index of item of minimum empty slot

    const int Inventory::getMinimum(Item& I) {
        for (int i = 0; i < 27; i++) {
            if (this->Inven[i] != nullptr && *this->Inven[i] == I && !this->Inven[i]->isFull()) return i;
        }
        return -1;
    } // Gets index of item of minimum same item

    const void Inventory::Show() {
        // Crafting
        for (int i = 0; i < 9; i++) {
            std::cout << "[ ";
            if (this->Crinv[i] != nullptr) {
                std::cout << this->Crinv[i];
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
                std::cout << this->Inven[i];
            } else {
                std::cout << "Empty";
            }
            std::cout << " ]";
            if (i % 9 == 8) std::cout << std::endl;
            else std::cout << " ";
        }
        std::cout << std::endl;
    } // Menampilkan Isi Inven dan Crafting

    void Inventory::Give(Config& c, std::string s, int i) {
        int minSameIdx, remainder;

        const Recipe *r = c.getRecipe(s);
        if (r->isTool) {
            // Inventory Full
            if (this->getMinimum() == -1) throw ContainerFullException();
            this->Inven[this->getMinimum()] = new Tool(r->id, r->name, r->type);
            if (i > 1) this->Give(c, s, i - 1);
        } else {
            NonTool nt = NonTool(r->id, r->name, r->type, 1);
            minSameIdx = this->getMinimum(nt);
            if (minSameIdx == -1) {
                // Inventory Full
                if (this->getMinimum() == -1) throw ContainerFullException();
                if (i > NonTool::MaxQuantity) {
                    this->Inven[this->getMinimum()] = new NonTool(r->id, r->name, r->type, NonTool::MaxQuantity);
                    this->Give(c, s, i - NonTool::MaxQuantity);
                } else {
                    this->Inven[this->getMinimum()] = new NonTool(r->id, r->name, r->type, i);
                }
            } else if (this->Inven[minSameIdx]->getAmt() + i < NonTool::MaxQuantity + 1) {
                this->Inven[minSameIdx]->setAmt(this->Inven[minSameIdx]->getAmt() + i);
            } else {
                remainder = i + this->Inven[minSameIdx]->getAmt() - NonTool::MaxQuantity;
                this->Inven[minSameIdx]->setAmt(NonTool::MaxQuantity);
                this->Give(c, s, remainder);
            }
        }
    } // Menambahkan Item pada Inventory

    void Inventory::Discard(int i, int n) {
        if (this->Inven[i] == nullptr) throw NotExistsException();
        if (this->Inven[i]->isTool()) {
            this->DeleteSlotContents(Inv, i);
        } else {
            if (this->Inven[i]->getAmt() > n) {
                this->Inven[i]->setAmt(this->Inven[i]->getAmt() - n);
            } else if (this->Inven[i]->getAmt() == n) {
                this->DeleteSlotContents(Inv, i);
            } else {
                throw NumberTooBigException();
            }
        }
    } // Membuang Item pada Inventory

    const bool Inventory::isCrash(Stype src, int i, Stype dst, int j) {
        Item *a, *b;

        if (src == Inv) a = this->Inven[i];
        else if (src == Cr) a = this->Crinv[i];

        if (dst == Inv) b = this->Inven[j];
        else if (dst == Cr) b = this->Crinv[j];

        if (b != nullptr && (                // Other slot is not empty
            a->isTool()  ||                  // Tool
            !(*a == *b)     ))               // Other slot not same item
            return true;
        return false;
    } // Auxiliary Function To Check for Item Crashing

    void Inventory::Move(Stype src, int i, int n, Stype dst, std::vector<int> j) {
        int moved;
        // Type 1
        if (src == Inv && dst == Cr) {
            if (this->Inven[i] == nullptr) throw NotExistsException();
            if ((this->Inven[i]->isTool() && n > 1) || (this->Inven[i]->getAmt() < n)) throw NumberTooBigException();
            for (int it = 0; it < n; it++) {
                if (this->isCrash(src, i, dst, j[it])) throw CrashSlotException();
            }

            if (n == 1 && this->Crinv[j[0]] == nullptr) {
                if (this->Inven[i]->isTool()) {
                    this->Crinv[j[0]] = this->Inven[i];
                    this->Inven[i] = nullptr;
                } else {
                    this->Crinv[j[0]] = new NonTool(this->Inven[i]->getId(), this->Inven[i]->getName(), this->Inven[i]->getType(), 1);
                    this->Inven[i]->setAmt(this->Inven[i]->getAmt() - 1);
                }
                if (this->Inven[i]->getAmt() == 0) this->DeleteSlotContents(Inv, i);
            } else if (!this->Inven[i]->isTool()) {
                for (int it = 0; it < n; it++) {
                    if (this->Crinv[j[it]] == nullptr) {
                        this->Crinv[j[it]] = new NonTool(this->Inven[i]->getId(), this->Inven[i]->getName(), this->Inven[i]->getType(), 1);
                        this->Inven[i]->setAmt(this->Inven[i]->getAmt() - 1);
                    } else {
                        this->Crinv[j[it]]->setAmt(this->Crinv[j[it]]->getAmt() + 1);
                        this->Inven[i]->setAmt(this->Inven[i]->getAmt() - 1);
                    }
                    if (this->Inven[i]->getAmt() == 0) this->DeleteSlotContents(Inv, i);
                }
            } else {
                throw WrongTypeException();
            }
        }
        // Type 2
        else if (src == Inv && dst == Inv) {
            if (this->Inven[i] == nullptr) throw NotExistsException();
            if (this->isCrash(src, i, dst, j[0])) throw CrashSlotException();

            if (this->Inven[j[0]] == nullptr) {
                this->Inven[j[0]] = this->Inven[i];
                this->Inven[i] = nullptr;
            } else {
                if (this->Inven[j[0]]->getAmt() + this->Inven[i]->getAmt() <= 64) {
                    this->Inven[j[0]]->setAmt(this->Inven[j[0]]->getAmt() + this->Inven[i]->getAmt());
                    this->DeleteSlotContents(Inv, i);
                } else {
                    moved = 64 - this->Inven[j[0]]->getAmt();
                    this->Inven[j[0]]->setAmt(64);
                    this->Inven[i]->setAmt(this->Inven[i]->getAmt() - moved);
                }

            }
        }
        // Type 3
        else if (src == Cr && dst == Inv) {
            if (this->Crinv[i] == nullptr) throw NotExistsException();
            if (this->isCrash(src, i, dst, j[0])) throw CrashSlotException();

            if (this->Inven[j[0]] == nullptr) {
                this->Inven[j[0]] = this->Crinv[i];
                this->Crinv[i] = nullptr;
            } else {
                if (this->Inven[j[0]]->getAmt() + this->Crinv[i]->getAmt() <= 64) {
                    this->Inven[j[0]]->setAmt(this->Inven[j[0]]->getAmt() + this->Crinv[i]->getAmt());
                    this->DeleteSlotContents(Cr, i);
                } else {
                    moved = 64 - this->Inven[j[0]]->getAmt();
                    this->Inven[j[0]]->setAmt(64);
                    this->Crinv[i]->setAmt(this->Crinv[i]->getAmt() - moved);
                }
            }
        }
    } // Generic Handler for Move command

    void Inventory::Use(int i) {
        if (this->Inven[i] == nullptr) throw NotExistsException();
        if (!this->Inven[i]->isTool()) throw WrongTypeException();
        this->Inven[i]->use();
        if (this->Inven[i]->getAmt() == 0) this->DeleteSlotContents(Inv, i);
    } // Use dari inventory

    void Inventory::Import(Config& c, std::string path) {
        std::ifstream inf(path);
        std::string line, token, num;
        std::string delimiter = ":";

        for (int i = 0; i < 9; i++) {
            if (this->Crinv[i] != nullptr) this->DeleteSlotContents(Cr, i);
        }

        for (int i = 0; i < 27; i++) {
            if (this->Inven[i] != nullptr) this->DeleteSlotContents(Inv, i);
        }

        while(std::getline(inf, line)) {
            token = line.substr(0, line.find(delimiter));
            num = line.erase(0, line.find(delimiter) + delimiter.length());
            if (num != "0") {
                const Recipe *r = c.getRecipe(std::stoi(token));
                if (r->isTool) {
                    this->Inven[this->getMinimum()] = new Tool(r->id, r->name, r->type, std::stoi(num));
                }
                else this->Give(c, r->name, std::stoi(num));
            }
        }

        std::cout << std::endl << "Import Successful" << std::endl;

    } // Import Inventory dari file .txt

    const void Inventory::Export(std::string path) {
        std::ofstream of(path);
        std::vector<int> idx(1);

        try {
            for (int i = 0; i < 9; i++) {
                if (this->Crinv[i] != nullptr) {
                    idx[0] = this->getMinimum(*this->Crinv[i]);
                    if (idx[0] == -1) idx[0] = this->getMinimum();
                    this->Move(Cr, i, 1, Inv, idx);
                }
            }
        } catch (Exception *e) {
            std::cout << std::endl << e->what() << std::endl;
        }

        std::cout << std::endl << "Moved Crafting Slot Items to Inventory." << std::endl;

        for (int i = 0; i < 27; i++) {
            if (this->Inven[i] != nullptr) of << this->Inven[i]->getId() << ":" << this->Inven[i]->getAmt() << std::endl;
            else of << "0:0" << std::endl;
        }

        std::cout << std::endl << "Export Successful" << std::endl;
        of.close();
    } // Melakukan export pada file .txt

    void Inventory::Help() {
        std::cout << "COMMANDS : \n";
        std::cout << "SHOW                                  : Menampilkan crafting table dan inventory\n";
        std::cout << "GIVE <NAME> <QTY>                     : Menambahkan Item ke Inventory\n";
        std::cout << "DISCARD <INV_SLOT_ID> <QTY>           : Membuang item di slot inventory dengan kuantitas yang diberikan\n";
        std::cout << "MOVE <INV_SLOT_ID> N <CRAFT_SLOT_ID>* : Memindahkan item dari slot inventory ke N slot crafting\n";
        std::cout << "MOVE <INV_SLOT_ID> 1 <INV_SLOT_ID>    : Menumpuk item pada kedua slot inventory\n";
        std::cout << "MOVE <CRAFT_SLOT_ID> 1 <INV_SLOT_ID>* : Memindahkan item dari slot crafting ke slot inventory\n";
        std::cout << "USE <INV_SLOT_ID>                     : Menggunakan Item, menurunkan durabilitas\n";
        std::cout << "CRAFT                                 : Craft Item\n";
        std::cout << "IMPORT <NAMA_FILE>                    : Import inventory dari <NAMA_FILE>\n";
        std::cout << "EXPORT <NAMA_FILE>                    : Export inventory dengan nama <NAMA_FILE>\n";
    } // Prints help

    std::pair<Inventory::Stype, int> Inventory::parseId(std::string id) {
        Inventory::Stype type;

        if (id[0] == 'I') type = Inventory::Inv;
        else if (id[0] == 'C') type = Inventory::Cr;
        else throw NotExistsException();

        int idx;
        std::stringstream stream(id.substr(1));
        stream >> idx;

        if (stream.fail()) throw NotExistsException();

        if ((type == Cr && (idx < 0 || idx >= 9)) || (type == Inv && (idx < 0 || idx >= 27)))
            throw NotExistsException();

        return std::pair<Inventory::Stype, int>(type, idx);
    }
}
