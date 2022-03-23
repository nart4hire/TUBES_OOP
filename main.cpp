#include <string>
#include <iostream>
#include <cctype>

#include "lib/Config.hpp"
#include "lib/Inventory.hpp"

using namespace mobicraft;

void printHelp();

int main(int argc, char *argv[])
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

  std::cout << "Welcome to MOBICRAFT. Type HELP for help, QUIT to quit.\n";

  Inventory inv;

  std::string cmd;
  do {
    std::cout << "> ";
    std::cin >> cmd;

    if (cmd == "HELP")
    {
      inv.Help();
    }
    else if (cmd == "SHOW")
    {
      inv.Show();
    }
  } while (cmd != "QUIT");

  std::cout << "Goodbye.\n";

  return 0;
}
