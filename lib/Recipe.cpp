#include "Recipe.hpp"
#include <iostream>

namespace mobicraft
{
  Recipe::Recipe(string name, int row, int col, std::vector<string> recipe, int quantity)
  {
    this->name = name;
    this->row = row;
    this->col = col;
    this->quantity = quantity;

    if (recipe.size() > CraftingTableSize)
    {
      // Throw
    }
    else if (recipe.size() < CraftingTableSize)
    {
      this->type = RecipeType::Submatrix;
    }
    else
    {
      this->type = RecipeType::Normal;
    }

    for (int i = 0; i < recipe.size(); i++)
    {
      this->recipe.push_back(recipe[i]);
    }
  }
}
