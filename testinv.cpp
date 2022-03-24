#include "lib/Inventory.hpp"
#include "lib/Config.hpp"

using namespace mobicraft;

int main(int argc, char const *argv[])
{
    std::string itemsFile("./config/item.txt");
    std::string recipesDir("./config/recipe");

    if (argc > 1 && argc < 3)
    {
        exit(1); // Abnormal Exit
    }
    else if (argc == 3)
    {
        itemsFile = argv[1];
        recipesDir = argv[2];
    }

    Config config(itemsFile, recipesDir);

    Inventory I;
    int idx[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int jdx[1] = { 26 };
    I.Give(config, "OAK_LOG", 1);
    try {
        I.Move(Inventory::Inv, 0, 1, Inventory::Inv, jdx);
    } catch (Exception *e) {
        std::cout << e->what() << std::endl;
    }
    I.Show();
    I.Give(config, "OAK_LOG", 1000);
    // for (int i = 0; i < 9; i++)
    // {
    //     I.Give(config, "WOODEN_SWORD", i);
    //     for (int j = 0; j < i; j++) I.Use(i);
    // }

    // for (int i = 0; i < 9; i++)
    // {
    //     I.Give(config, "OAK_LOG", i + 1);
    //     for (int j = 0; j < i; j++) I.Use(i);
    // }
    try {
        for (int i = 0; i < 7; i++) I.Move(Inventory::Inv, 0, 9, Inventory::Cr, idx);
    } catch (Exception *e) {
        std::cout << e->what() << std::endl;
    }
    I.Show();

    I.Export("./Test.txt");

    return 0;
}
