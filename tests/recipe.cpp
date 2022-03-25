#include <iostream>
#include <string>
#include "../lib/Recipe.hpp"

#include "../lib/Recipe.cpp"
#include "../lib/Item.cpp"
#include "../lib/NonTool.cpp"
#include "../lib/Tool.cpp"

using namespace mobicraft;

int main(void)
{
  std::cout << "\nCreate non-tool recipe.\n";
  Recipe *nt = new NonToolRecipe(1, "OAK_PLANK", "PLANK");

  std::cout << "\nCreate recipe grid.\n";
  Grid<std::string> ntGrid(1, 1);
  ntGrid.at(0, 0) = "OAK_LOG";

  nt->set(ntGrid, 4);
  ntGrid.print();

  std::cout << "\nCompare with grid.\n"
            << (*nt == ntGrid);

  std::cout << "\nCreate item.\n";
  Item *i = nt->create();
  std::cout << i;

  std::cout << "\nCreate tool recipe.\n";
  Recipe *t = new ToolRecipe(1, "IRON_SWORD", "-");

  std::cout << "\nCreate recipe grid.\n";
  Grid<std::string> tGrid(3, 1);
  tGrid.at(0, 0) = "IRON_INGOT";
  tGrid.at(1, 0) = "IRON_INGOT";
  tGrid.at(2, 0) = "STICK";

  std::cout << "\nSet invalid quantity.\n";
  try
  {
    t->set(tGrid, 4);
  }
  catch(const Exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  std::cout << "\nSet valid quantity.\n";
  t->set(tGrid, 1);

  std::cout << "\nCompare with grid.\n"
            << (*t == tGrid);

  std::cout << "\nCreate item.\n";
  delete i;
  i = t->create();
  std::cout << i;

  delete t;
  delete i;
  delete nt;

  return 0;
}
