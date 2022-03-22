#include "Recipe.hpp"
#include <iostream>

#include "Tool.hpp"
#include "NonTool.hpp"

namespace mobicraft
{
  Recipe::Recipe(int id, std::string name, std::string type)
      : id(id), name(name), type(type)
  {
  }

  bool Recipe::operator==(const Grid<std::string> &table) const
  {
    auto reduced = table.reduce(std::string("-"));
    return recipe == reduced || recipe.flipVertically() == reduced;
  }

  bool Recipe::operator!=(const Grid<std::string> &table) const
  {
    return !(*this == table);
  }

  ToolRecipe::ToolRecipe(int id, std::string name, std::string type)
      : Recipe(id, name, type)
  {
  }

  void ToolRecipe::set(const Grid<std::string> &recipe, int quantity)
  {
    if (quantity != 1)
    {
      // error
    }

    this->recipe = recipe;
  }

  Item *ToolRecipe::create()
  {
    return new Tool(id, name, type);
  }

  NonToolRecipe::NonToolRecipe(int id, std::string name, std::string type)
      : Recipe(id, name, type)
  {
  }

  void NonToolRecipe::set(const Grid<std::string> &recipe, int quantity)
  {
    if (quantity < 1)
    {
      // error
    }

    this->recipe = recipe;
    this->quantity = quantity;
  }

  Item *NonToolRecipe::create()
  {
    return new NonTool(id, name, type, quantity);
  }
}
