#include "Recipe.hpp"
#include <iostream>

namespace mobicraft
{
  Recipe::Recipe(std::string name, Grid<std::string> recipe, int quantity)
      : name(name), recipe(recipe), quantity(quantity)
  {
  }

  bool Recipe::operator==(const Grid<std::string> &table) const
  {
    auto reduced = table.reduce(std::string("-"));
    return recipe == reduced || recipe.flipVertically() == reduced;
  }
}
