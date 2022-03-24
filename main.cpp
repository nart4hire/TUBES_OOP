#include <string>
#include <iostream>
#include <cctype>
#include <sstream>

#include "lib/Config.hpp"
#include "lib/Inventory.hpp"
#include "lib/Exception.hpp"

using namespace mobicraft;

int toInt(std::string str);

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
  try
  {
    config.load();
  }
  catch (const Exception &e)
  {
    std::cout << "Error while loading config file:\n"
              << e.what() << "\n";
    exit(1);
  }

  std::cout << "Welcome to MOBICRAFT. Type HELP for help, QUIT to quit.\n";
  config.printStatus();

  Inventory inv;

  std::string cmd;
  do
  {
    std::cout << "\n> ";
    std::cin >> cmd;

    try
    {
      if (cmd == "HELP")
      {
        inv.Help();
      }
      else if (cmd == "SHOW")
      {
        inv.Show();
      }
      else if (cmd == "GIVE")
      {
        std::string name;
        int qty;
        std::cin >> name;
        std::cin >> qty;
        inv.Give(config, name, qty);
      }
      else if (cmd == "USE")
      {
        std::string id;
        std::cin >> id;

        if (id[0] == 'I')
          inv.Use(toInt(id.substr(1)));
      }
      else if (cmd == "CRAFT")
      {
        // CRAFT
      }
      else if (cmd == "IMPORT")
      {
        std::string fname;
        std::cin >> fname;
        inv.Import(config, fname);
      }
      else if (cmd == "EXPORT")
      {
        std::string fname;
        std::cin >> fname;
        inv.Export(fname);
      }
      else if (cmd == "MOVE")
      {
        // MOVE
      }
    }
    catch (const Exception &e)
    {
      std::cout << "Error ("<< e.getId() << ") : "
                << e.what() << "\n";
    }
    catch (...)
    {
      std::cout << "An unknown error occured.\n";
    }
  } while (cmd != "QUIT");

  std::cout << "Goodbye.\n";

  return 0;
}

int toInt(std::string str)
{
  int val;
  std::stringstream stream(str);
  stream >> val;
  return val;
}
