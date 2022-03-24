#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <utility>
#include <vector>

#include "lib/Config.hpp"
#include "lib/Inventory.hpp"
#include "lib/Crafting.hpp"
#include "lib/Exception.hpp"

using namespace mobicraft;

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

    std::string line;
    std::getline(std::cin, line);
    std::stringstream input(line);

    try
    {
      input >> cmd;
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
        input >> name;
        input >> qty;

        if (input.fail())
          throw InvalidQuantityException();

        inv.Give(config, name, qty);
      }
      else if (cmd == "DISCARD")
      {
        std::string id;
        input >> id;

        auto parsed = Inventory::parseId(id);

        int qty;
        input >> qty;

        if (input.fail())
          throw InvalidQuantityException();

        inv.Discard(parsed.second, qty);
      }
      else if (cmd == "USE")
      {
        std::string id;
        input >> id;

        auto parsed = Inventory::parseId(id);
        inv.Use(parsed.second);
      }
      else if (cmd == "CRAFT")
      {
        Crafting craft(config, inv);
        craft.crafting();
      }
      else if (cmd == "IMPORT")
      {
        std::string fname;
        input >> fname;
        inv.Import(config, fname);
      }
      else if (cmd == "EXPORT")
      {
        std::string fname;
        input >> fname;
        inv.Export(fname);
      }
      else if (cmd == "MOVE")
      {
        std::string srcId;
        input >> srcId;

        auto src = Inventory::parseId(srcId);
        int qty;
        input >> qty;

        if (input.fail())
          throw InvalidQuantityException();

        std::string destId;
        input >> destId;

        auto dest = Inventory::parseId(destId);

        std::vector<int> dests;
        dests.push_back(dest.second);

        if (dest.first == Inventory::Cr)
        {
          while (input >> destId)
          {
            dest = Inventory::parseId(destId);
            if (dest.first != Inventory::Cr)
              throw InvalidCommandException();
            dests.push_back(dest.second);
          }

          if (qty < dests.size())
            throw InvalidCommandException();
        }

        inv.Move(src.first, src.second, qty, dest.first, {/* dests */});
      }
      else
      {
        throw InvalidCommandException();
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
