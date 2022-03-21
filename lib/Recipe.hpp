#ifndef RECIPE_H
#define RECIPE_H

#include <string>

#include "Grid.hpp"

namespace mobicraft
{
  class Recipe
  {
    std::string name;
    Grid<std::string> recipe;
    int quantity;

  public:
    Recipe(std::string name, Grid<std::string> recipe, int quantity);
    bool operator==(const Grid<std::string> &table) const;
    bool operator!=(const Grid<std::string> &table) const;
  };
}

#endif
