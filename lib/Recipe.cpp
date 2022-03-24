#include <iostream>

#include "Recipe.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#include "Exception.hpp"

namespace mobicraft
{
  Recipe::Recipe(int id, std::string name, std::string type, bool isTool)
      : id(id), name(name), type(type), isTool(isTool)
  {
  }

  bool Recipe::isCraftable() const
  {
    return !recipe.isNull();
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
      : Recipe(id, name, type, true)
  {
  }

  void ToolRecipe::set(const Grid<std::string> &recipe, int quantity)
  {
    if (quantity != 1)
    {
      throw InvalidQuantityException();
    }

    this->recipe = recipe;
  }

  Item *ToolRecipe::create()
  {
    return new Tool(id, name, type);
  }

  int ToolRecipe::getAmt(){
    return this->durability;
  }

  NonToolRecipe::NonToolRecipe(int id, std::string name, std::string type)
      : Recipe(id, name, type, false)
  {
  }

  void NonToolRecipe::set(const Grid<std::string> &recipe, int quantity)
  {
    if (quantity < 1)
    {
      throw InvalidQuantityException();
    }

    this->recipe = recipe;
    this->quantity = quantity;
  }

  Item *NonToolRecipe::create()
  {
    return new NonTool(id, name, type, quantity);
  }

  int NonToolRecipe::getAmt(){
    return this->quantity;
  }
}
