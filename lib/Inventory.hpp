#ifndef INVEN_HEADER
#define INVEN_HEADER

#include <iterator>
#include <map>
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

        // Command Handler
        friend std::istream& operator>>(std::istream&, Inventory&);

        // Methods

        Item* getInven(int idx);

        void setInven(int idx, Item* item);

        Item* getCrinv(int idx);

        void setCrinv(int idx, Item* item);

        void DeleteSlotContents(Stype, int); // Auxiliary for deleting items in inventory slots

        const int getMinimum(); // Gets index of ItemPTR of minimum empty slot

        const int getMinimumSameItem(Item&); // Gets Index of the same item with contents 0 <= x <= 64

        const void Show(); // Menampilkan Isi Inven dan Crafting

        void Give(Config&, std::string, int); // Menambahkan Item pada Inventory

        void Discard(int, int); // Membuang Item pada Inventory

        const bool isCrash(Stype, int, Stype, int); // Auxiliary Function To Check for Item Crashing

        void Move(Stype, int, int, Stype, int*); // Generic Handler for Move command

        void Use(int); // Use dari inventory

        void Craft(); // Melakukan Crafting

        void Import(Config, std::string); // Import Inventory dari file .txt

        const void Export(std::string); // Melakukan export pada file .txt

        void Help(); // Prints help
    };

}

#endif