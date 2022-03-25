#include "../lib/Inventory.hpp"
#include "../lib/Config.hpp"

// Needed because unit testing
#include "../lib/Inventory.cpp"
#include "../lib/Recipe.cpp"
#include "../lib/Config.cpp"
#include "../lib/Item.cpp"
#include "../lib/NonTool.cpp"
#include "../lib/Tool.cpp"

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
    config.load();

    Inventory I;
    int idx[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int jdx[1] = { 26 };

    I.Give(config, "OAK_LOG", 1);
    I.Show();
    try {
        I.Move(Inventory::Inv, 0, 1, Inventory::Inv, jdx);
    } catch (Exception *e) {
        std::cout << e->what() << std::endl;
    }
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

    I.Export("./tests/Test.txt");
    I.Import(config, "./tests/Test.txt");

    return 0;
}
