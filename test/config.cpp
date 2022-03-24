#include "../lib/Config.hpp"

using namespace mobicraft;

int main(void)
{
  std::cout << "Load config from default files.\n";

  Config config("../../config/item.txt", "../../config/recipe");
  try
  {
    config.load();
  }
  catch(const Exception &e)
  {
    std::cout << "Error: " << e.what() << "\n";
  }

  std::cout << "\nPrint status\n";
  config.printStatus();

  std::cout << "\nPrint all recipes\n";
  for (const auto &i : config.getRecipes())
  {
    std::cout << i->name << "\n";
  }

  std::cout << "\nGet existing recipe: name = OAK_LOG\n";
  try
  {
    config.getRecipe("OAK_LOG");
  }
  catch(const Exception &e)
  {
    std::cout << "Error: " << e.what() << "\n";
  }

  std::cout << "\nGet nonexistent recipe: name = LOG\n";
  try
  {
    config.getRecipe("LOG");
  }
  catch(const Exception &e)
  {
    std::cout << "Error: " << e.what() << "\n";
  }

  std::cout << "\nGet existing recipe: id = 1\n";
  try
  {
    config.getRecipe(1);
  }
  catch(const Exception &e)
  {
    std::cout << "Error: " << e.what() << "\n";
  }

  std::cout << "\nGet nonexistent recipe: id = 100\n";
  try
  {
    config.getRecipe(100);
  }
  catch(const Exception &e)
  {
    std::cout << "Error: " << e.what() << "\n";
  }

  std::cout << "\nLoad config from nonexistent files.\n";

  Config config2("item.txt", "recipe");
  try
  {
    config2.load();
  }
  catch(const Exception &e)
  {
    std::cout << "Error: " << e.what() << "\n";
  }
  
  return 0;
}
