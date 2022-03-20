#ifndef RECIPE_H
#define RECIPE_H

#include <string>
#include <vector>

using std::string;

namespace mobicraft
{
  const int CraftingTableSize = 9;

  enum class RecipeType
  {
    Submatrix,
    Normal
  };

  class Recipe
  {
    string name;
    int row, col;
    std::vector<string> recipe;
    int quantity;
    RecipeType type;

  public:
    Recipe(string name, int row, int col, std::vector<string> recipe, int quantity);
    bool operator==(std::vector<string> table);
  };
}

#endif
