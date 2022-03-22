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
    for (int i = 0; i < 9; i++)
    {
        I.Give(config, "WOODEN_SWORD", i);
        for (int j = 0; j < i; j++) I.Use(i);
    }

    for (int i = 0; i < 9; i++)
    {
        I.Give(config, "OAK_LOG", i + 1);
        for (int j = 0; j < i; j++) I.Use(i);
    }

    I.Show();

    return 0;
}
