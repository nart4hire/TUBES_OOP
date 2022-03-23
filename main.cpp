#include <string>
#include <iostream>
#include <cctype>

#include "lib/Config.hpp"

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

  std::string cmd;
  do {
    std::cout << "> ";
    std::cin >> cmd;

    if (cmd == "HELP")
    {
      printHelp();
    }
  } while (cmd != "QUIT");

  std::cout << "Goodbye.\n";

  return 0;
}

void printHelp()
{
  // Help
  std::cout << "COMMANDS : \n";
  std::cout << "SHOW                                  : Menampilkan crafting table dan inventory\n";
  std::cout << "GIVE <NAME> <QTY>                     : Menambahkan Item ke Inventory\n";
  std::cout << "DISCARD <INV_SLOT_ID> <QTY>           : Membuang item di slot inventory dengan kuantitas yang diberikan\n";
  std::cout << "MOVE <INV_SLOT_ID> N <CRAFT_SLOT_ID>* : Memindahkan item dari slot inventory ke N slot crafting\n";
  std::cout << "MOVE <INV_SLOT_ID> 1 <INV_SLOT_ID>    : Menumpuk item pada kedua slot inventory\n";
  std::cout << "MOVE <CRAFT_SLOT_ID> 1 <INV_SLOT_ID>* : Memindahkan item dari slot crafting ke slot inventory\n";
  std::cout << "USE <INV_SLOT_ID>                     : Menggunakan Item, menurunkan durabilitas\n";
  std::cout << "CRAFT                                 : Craft Item\n";
  std::cout << "EXPORT <NAMA_FILE>                    : Export inventory dengan nama <NAMA_FILE>\n";
}
