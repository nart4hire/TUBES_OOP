#ifndef INVEN_HEADER
#define INVEN_HEADER

#include <utility>
#include <vector>
#include "Exception.hpp"
#include "Config.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"


namespace mobicraft {
    class Inventory
    {
    private:
        Item **Inven;
        Item **Crinv;

    public:
        enum Stype {Inv = 0, Cr = 1}; // Declare

        // ctor
        Inventory();

        // dtor
        ~Inventory();

        // Methods

        // Inven getter
        Item* getInven(int idx);

        // Inven setter
        void setInven(int idx, Item* item);

        // Crinv getter
        Item* getCrinv(int idx);

        // Crinv setter
        void setCrinv(int idx, Item* item);

        // Return the minimum quantity of all items in Crinv
        int getMinQtyInCrinv() const;

        int sumCrinvToolsDurability() const;

        // Auxiliary for deleting items in inventory slots
        void DeleteSlotContents(Stype, int);

        // Gets index of ItemPTR of minimum empty slot
        const int getMinimum();

        // Gets Index of the same item with contents 0 <= x <= 64
        const int getMinimum(Item&);

        // Menampilkan Isi Inven dan Crafting
        const void Show();

        // Menambahkan Item pada Inventory
        void Give(Config&, std::string, int);

        // Membuang Item pada Inventory
        void Discard(int, int);

        // Auxiliary Function To Check for Item Crashing
        const bool isCrash(Stype, int, Stype, int);

        // Generic Handler for Move command
        void Move(Stype, int, int, Stype, std::vector<int>);

        // Use dari inventory
        void Use(int);

        // Import Inventory dari file .txt
        void Import(Config&, std::string);

        // Melakukan export pada file .txt
        const void Export(std::string);

        // Prints help
        void Help();

        // Returns slot type and index from a given id string
        static std::pair<Stype, int> parseId(std::string);
    };

}

#endif